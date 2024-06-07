#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//判断指定位是否为0，若index位为0，则GET_BYTE值为假，否则为真
#define GET_BYTE(value, index) (((value) & (1 << ((index) ^ 7))) != 0)
//将指定位，置为1
#define SET_BYTE(value, index) ((value) |= (1 << ((index) ^ 7)))
//将指定位，置为0
#define CLR_BYTE(value, index) ((value) &= (~(1 << ((index) ^ 7))))

typedef unsigned char u8;

typedef struct huffman{
	int character;
	int freq;
}HUFFMAN;

//哈夫曼树的节点
typedef struct huff{
        //字符及其频率
	HUFFMAN freq;
        //左孩子
	int left;
        //右孩子
	int right;
        //是否用过0表示没有用过1表示用过
	int use;
        //该节点对于的哈夫曼编码字符串
	char *code;
}Huff;

//查找到频率最小的字符的下标
int searchmin(Huff *freq, int count){
	int i;
	int minindex = -1;
	
	for(i = 0; i < count; i++){
		if(freq[i].use == 0){
			minindex = i;
			break;
		}
	}
	if(minindex == -1){
		return -1;
	}
	for(i = 0; i < count; i++){
		if((freq[i].freq.freq <= freq[minindex].freq.freq) && freq[i].use == 0){
			minindex = i;
		}
	}
	freq[minindex].use = 1;
	return minindex;
}

//创建哈夫曼树
Huff *bulidhuftree(HUFFMAN *information, int *count){
	int i;
	int degree = 2*(*count) - 1;
	Huff *result;
	int temp;
 
	//将生成的哈夫曼树放在result里返回
	result = (Huff *)calloc(sizeof(Huff), degree);
        //填充基本字符及其频度
	for(i = 0; i < *count; i++){
		result[i].freq.freq = information[i].freq;
		result[i].freq.character= information[i].character;
		result[i].left = -1;
		result[i].right = -1;
		result[i].use = 0;
		result[i].code = (char*)malloc(sizeof(char)*(*count));
	}
	//根据基本字符及其频度填充哈夫曼表
	for(i = *count; i < degree; i++){
		result[i].use = 1;
		result[i].freq.character = '#';
		result[i].right = searchmin(result, *count);
		result[i].left = searchmin(result, *count);
		result[i].freq.freq = result[result[i].right].freq.freq + result[result[i].left].freq.freq;
		temp  = searchmin(result, ++(*count));
		if(temp == -1){
			break;
		}
		result[temp].use = 0;
		result[i].use = 0;
	}
	return result;
}

//根节点所在的下标，index为字符串下标，str为字符串，
void bulidhuftreecode(int root, int index, Huff *freq, char *str){
	//采用递归，此处是哈夫曼压缩最难得地方，建议大家根据代码遍历跟踪一遍
	if(freq[root].left != -1 && freq[root].right != -1){
		str[index] = '1';
		bulidhuftreecode(freq[root].left, index+1, freq, str);
		str[index] = '0';
		bulidhuftreecode(freq[root].right, index+1, freq, str);
	}
	else{
		str[index] = 0;
		strcpy(freq[root].code, str);
	}	
}

HUFFMAN *freqhuf(int *count, char *goalfile, int *lastindex){
	int i;
	HUFFMAN *result;
	FILE *fpIn;
	
	fpIn = fopen(goalfile, "rb");
	if(fseek(fpIn, 3L, SEEK_SET) == 0){
		fread(count, sizeof(char),  1, fpIn);
		fread(lastindex, sizeof(char),  1, fpIn);
	}
	result = (HUFFMAN *)calloc(sizeof(HUFFMAN), *count);
	if(fseek(fpIn, 12L, SEEK_SET) == 0){
		fread(result, sizeof(HUFFMAN), *count, fpIn);
	}
	fclose(fpIn);
	return result;
}

void creatsourcefile(Huff *freq, int count, char *goalfile, char *resultfile, int lastindex){
	FILE *fpOut;
	FILE *fpIn;
	long temp;
	u8 value;
	int index = 0;
	int root;
	long bitecount;
	int fininsh = 0;
	
	fpIn = fopen(goalfile, "rb");
	fseek(fpIn, 0L, SEEK_END);
	bitecount = ftell(fpIn);
	fclose(fpIn);
	
	root = count - 1;
	temp = (long)(count + 1)/2;
	fpOut = fopen(resultfile, "wb");
	fpIn = fopen(goalfile, "rb");
	if(fseek(fpIn, temp * 8 + 12, SEEK_SET) == 0){
		printf("decompressing...\n");
		fread(&value, sizeof(char), 1, fpIn);
		while(!fininsh){
			if(GET_BYTE(value, index) == 0){
				root = freq[root].right;
			}
			if(GET_BYTE(value, index) == 1){
				root = freq[root].left;
			}
			if(freq[root].right == -1 && freq[root].right == -1){
				fwrite(&freq[root].freq.character, sizeof(char), 1, fpOut);
				root = count - 1;
			}
			if(++index >= 8){
                if(ftell(fpIn) == bitecount){
                    if(index >= lastindex){
                        fininsh = 1;
                    }
                }	
				index = 0;
				fread(&value, sizeof(char), 1, fpIn);
			}
	
		}
		printf("decompress successed! \n");	
	}
	else{
		printf("decompress failed! \n");
	}
}

int main(int argc, char *argv[]) {
	int count = 0;
	HUFFMAN *information;
	Huff *freq;
	char *str;
	char 	resultfile[50];
	char  goalfile[50];
	FILE *fp;
	char Huf[3];
	int lastindex = 0;
	int i;
	int password;
	int unpassword;
	
	fp = fopen(argv[1], "rb");
	if(fp == NULL){
		printf("file not found! ");
		return 0;
	}
	fread(&Huf, sizeof(char), 3, fp);
	if(Huf[0] != 'M' || Huf[1] != 'u' || Huf[2] != 'f'){
		printf("file is not a huffman compressed file! ");
		return 0;
	}
	if(fseek(fp, 8L, SEEK_SET) == 0){
		fread(&password, sizeof(int), 1, fp);
		printf("please enter password: ");
		scanf("%d", &unpassword);
		if(password != unpassword){
			printf("wrong password! ");
			return 0;
		}
	}
	fclose(fp);
	fp = fopen(argv[2], "w");
	fclose(fp);
	strcpy(goalfile, argv[1]);
	strcpy(resultfile, argv[2]);
	
	information = freqhuf(&count, goalfile, &lastindex);
	str = (char*)malloc(sizeof(char)*(count+1));  //临时数组存每个字符code
	freq = bulidhuftree(information, &count);
	bulidhuftreecode(count - 1, 0, freq, str);
	free(str);
	creatsourcefile(freq, count, goalfile, resultfile, lastindex);
	
	free(information);
	for(i = 0; i < count; i++){
		free(freq[i].code);
	}
	free(freq);
	free(str);
	return 0;  
}
