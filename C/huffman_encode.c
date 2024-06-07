#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//判断指定位是否为0，若index位为0，则GET_BYTE值为假，否则为真
#define GET_BYTE(value, index) (((value) & (1 << ((index) ^ 7))) != 0)
//将指定位，置为1
#define SET_BYTE(value, index) ((value) |= (1 << ((index) ^ 7)))
//将指定位，置为0
#define CLR_BYTE(value, index) ((value) &= (~(1 << ((index) ^ 7))))

typedef struct huffman{
	int character;
	int freq;
}HUFFMAN;

//count初值为0，传过来用于统计多少种字符，goalfile，为文件名称
HUFFMAN *freqhuf(int *count, char *goalfile){
	int freq[256] = {0};
	int i;
	int index;
	HUFFMAN *result;
	FILE *fpIn;
	int ch;
	
	fpIn = fopen(goalfile, "rb");
	ch = fgetc(fpIn);
//统计所有字符，这里巧妙的采用哈希算法，用字符的ASCII码值作为下标，
//freq[ASCII]的值，作为该字符的频率，很巧妙的形成字符和其频率的映射关系
	while (!feof(fpIn)) {
		freq[ch]++;
		ch = fgetc(fpIn);
	}
	fclose(fpIn);
//统计多少种字符
	for(i = 0; i < 256; i++){
		if(freq[i] != 0){
			(*count)++;
		}
	}
//将统计的结果，字符和其频率生成数组返回出去。
	result = (HUFFMAN *)calloc((2*(*count) - 1), sizeof(HUFFMAN));
	for(i = 0,index = 0; i < 256; i++){
		if(freq[i] != 0){
			result[index].character = i;
			result[index++].freq = freq[i];
		}
	}
	return result;
}

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

typedef unsigned char u8;
//压缩文件的头信息
typedef struct message{
        //前三个字节用M，u,f代表哈夫曼文件，不是这三个字符代表该文件不是压缩文件
 	u8 ishuf[3];
        //字符数量
 	u8 count;
        //最后一个字符所对应的下标
 	u8 lastindex;
        //密码（密码可以用自己学过的加密方式加密，这里我没有用加密算法）
 	int password;
}MESSAGE;

//得到哈夫曼文件最后一个字节第几个是有效位
int howlongchar(Huff *freq, int count){
	int i;
	long long sum = 0;
	
	for(i = 0; i < (count + 1)/2; i++){
		sum = sum + strlen(freq[i].code) * freq[i].freq.freq;
		//sum &= 0xFF;
	}
	return sum % 8 == 0 ? 8 : sum % 8;
}

//创建压缩文件
void creatcodefile(Huff *freq, int count, char *goalfile, char *resultfile, HUFFMAN *storefreq){
	FILE *fpOut;
	FILE *fpIn;
	unsigned char value;
	int i;
	int index = 0;
	const char *hufCode;
	int arr[256];
	int ch;
	int password;
	MESSAGE headcode = {'M', 'u', 'f'};
 
	//将密码存入文件头信息
	printf("please set compres password: ");
	scanf("%d", &headcode.password);
	printf("compressing...\n");
	
	fpOut = fopen(resultfile, "wb");
	fpIn = fopen(goalfile, "rb");
	headcode.count = (u8)(count + 1)/2;
	headcode.lastindex = howlongchar(freq, count);
        //将文件头信息写入文件
	fwrite(&headcode, sizeof(MESSAGE), 1, fpOut);
        //将字符和其频率写入文件
	fwrite(storefreq, sizeof(HUFFMAN), (count + 1)/2, fpOut);
	
	for(i = 0; i < (count + 1)/2; i++){
		arr[freq[i].freq.character] = i;
	}
        //遍历源文件，将每个字符按其哈夫曼编码写入新文件
	ch = fgetc(fpIn);
	while(!feof(fpIn)){
		hufCode = freq[arr[ch]].code;
		for(i = 0; hufCode[i]; i++){
			if(hufCode[i] == '0'){
				CLR_BYTE(value, index);
			}
			if(hufCode[i] == '1'){
				SET_BYTE(value, index);
			}
			if(++index >= 8){
				index = 0;
				fwrite(&value, 1, 1, fpOut);
			}
		}
		ch = fgetc(fpIn);
	}
	if(index){
		fwrite(&value, 1, 1, fpOut);
	}
	fclose(fpIn);
	fclose(fpOut);
}

int main(int argc, char *argv[]) {
	int count = 0;
	HUFFMAN *information;
	Huff *freq;
	char *str;
	char 	resultfile[50];
	char  goalfile[50];
	FILE *fp;
	int i;
	
	fp = fopen(argv[1], "r");
	if(fp == NULL){
		printf("file not found! ");
		return 0;
	}
	fclose(fp);
	fp = fopen(argv[2], "w");
	fclose(fp);	
	strcpy(goalfile, argv[1]);
	strcpy(resultfile, argv[2]);
	//统计字符
	information = freqhuf(&count, goalfile);
        //临时数组存每个字符code
	str = (char*)malloc(sizeof(char)*(count+1));
        //构建哈夫曼树
	freq = bulidhuftree(information, &count);
        //构建哈夫曼编码
	bulidhuftreecode(count - 1, 0, freq, str);
        //创建压缩文件
	creatcodefile(freq, count, goalfile, resultfile, information);
	//释放内存
	free(information);
	free(str);
	for(i = 0; i < count; i++){
		free(freq[i].code);
	}
	free(freq);
	printf("compresed successed! ");
	
	return 0;  
}
