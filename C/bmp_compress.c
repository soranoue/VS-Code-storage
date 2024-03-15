#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "sys/stat.h"
#include "fcntl.h"

typedef struct BMP_FILE_HEADER_t
{  
    uint32_t bfSize; 
    uint16_t bfReserved1; 
    uint16_t bfReserved2; 
    uint32_t bfOffBits;
}BMP_FILE_HEADER;//12 bytes

typedef struct BMP_INFO_HEADER_t
{
    uint32_t      biSize;
    int32_t       biWidth;
    int32_t       biHeight;
    uint16_t      biPlanes;
    uint16_t      biBitCount;
    uint32_t      biCompression;
    uint32_t      biSizeImage;
    int32_t       biXPelsPerMeter;
    int32_t       biYPelsPerMeter;
    uint32_t      biClrUsed;
    uint32_t      biClrImportant;
}BMP_INFO_HEADER;//40 bytes

typedef struct BMP_COLOR_TBL_t
{
    uint8_t B;
    uint8_t G;
    uint8_t R;
    uint8_t A;
}BMP_COLOR_TBL;

typedef struct BMP_DATA_t
{
    BMP_FILE_HEADER bmpFileHeader;
    BMP_INFO_HEADER bmpInfoHeader;
    uint8_t*           dataPtr;
}BMP_DATA;

void saveBmpDataToFile_colorTBL(uint8_t * data_p,uint32_t pixelW,uint32_t pixelH,uint32_t pixelS,uint8_t * colorTbl,uint32_t colorTblSize,char * path)
{
    if(colorTblSize==0) {printf("error! colorTblSize could not be zero!!!\n");return;};
    //s0 compute key parameters info
    uint32_t imageSize = pixelW * pixelH * pixelS;
    uint32_t bitsPerPixel = pixelS <<3;
    uint32_t imageDataOffsetFromHead       = 2+colorTblSize+sizeof(BMP_INFO_HEADER) + sizeof(BMP_FILE_HEADER);
    uint32_t imageDataOffsetFromFileHeader = sizeof(BMP_INFO_HEADER);
    uint32_t fileSize                      = 2+colorTblSize+imageSize+ sizeof(BMP_INFO_HEADER) + sizeof(BMP_FILE_HEADER);
    FILE * fp = fopen(path,"wb");
    //s1 save 'B' 'M'
    char Format_BM[2]={'B','M'};
    fwrite(Format_BM,sizeof(char),2,fp);
    //s2 save 12 bytes File Header
    BMP_FILE_HEADER fileHeader;
    fileHeader.bfOffBits  = imageDataOffsetFromHead;
    fileHeader.bfSize     = fileSize;
    fileHeader.bfReserved1=0;
    fileHeader.bfReserved2=0;
    fwrite(&fileHeader,sizeof(BMP_FILE_HEADER),1,fp);
    //s3 save 40 bytes Info Header
    BMP_INFO_HEADER infoHeader;
    infoHeader.biSize           = imageDataOffsetFromFileHeader;
    infoHeader.biWidth          = pixelW;
    infoHeader.biHeight         = pixelH;
    infoHeader.biPlanes         = 1;
    infoHeader.biBitCount       = bitsPerPixel;
    infoHeader.biCompression    = 0;
    infoHeader.biSizeImage      = pixelW*pixelH*1;
    infoHeader.biXPelsPerMeter  = 37795;
    infoHeader.biYPelsPerMeter  = 37795;
    infoHeader.biClrUsed        = 0;
    infoHeader.biClrImportant   = 0;
    fwrite(&infoHeader,sizeof(BMP_INFO_HEADER),1,fp);
    //s4 save color table
    fwrite(colorTbl,sizeof(uint8_t),colorTblSize,fp);
    //s5 save image data with inversed lines
    for(uint32_t i = 0;i<pixelH;i++)
    {
        fwrite(data_p+(pixelH-i-1)*(pixelW*pixelS),sizeof(uint8_t),pixelW*pixelS,fp);
    }
    fclose(fp);
}

void saveBmpDataToFile(uint8_t * data_p,uint32_t pixelW,uint32_t pixelH,uint32_t pixelS,char *path)
{
    //s0 compute key parameters info
    uint32_t imageSize = pixelW * pixelH * pixelS;
    uint32_t bitsPerPixel = pixelS <<3;
    uint32_t imageDataOffsetFromHead       = 2+sizeof(BMP_INFO_HEADER) + sizeof(BMP_FILE_HEADER);
    uint32_t imageDataOffsetFromFileHeader = sizeof(BMP_INFO_HEADER);
    uint32_t fileSize                      = 2+imageSize + sizeof(BMP_INFO_HEADER) + sizeof(BMP_FILE_HEADER);
    FILE * fp = fopen(path,"wb");
    //s1 save 'B' 'M'
    char Format_BM[2]={'B','M'};
    fwrite(Format_BM,sizeof(char),2,fp);
    //s2 save 12 bytes File Header
    BMP_FILE_HEADER fileHeader;
    fileHeader.bfOffBits  = imageDataOffsetFromHead;
    fileHeader.bfSize     = fileSize;
    fileHeader.bfReserved1=0;
    fileHeader.bfReserved2=0;
    fwrite(&fileHeader,sizeof(BMP_FILE_HEADER),1,fp);
    //s3 save 40 bytes Info Header
    BMP_INFO_HEADER infoHeader;
    infoHeader.biSize           = imageDataOffsetFromFileHeader;
    infoHeader.biWidth          = pixelW;
    infoHeader.biHeight         = pixelH;
    infoHeader.biPlanes         = 1;
    infoHeader.biBitCount       = bitsPerPixel;
    infoHeader.biCompression    = 0;
    infoHeader.biSizeImage      = imageSize;
    infoHeader.biXPelsPerMeter  = 37795;
    infoHeader.biYPelsPerMeter  = 37795;
    infoHeader.biClrUsed        = 0;
    infoHeader.biClrImportant   = 0;
    fwrite(&infoHeader,sizeof(BMP_INFO_HEADER),1,fp);
    //s4 save image data with inversed lines
    for(uint32_t i = 0;i<pixelH;i++)
    {
        fwrite(data_p+(pixelH-i-1)*(pixelW*pixelS),sizeof(uint8_t),pixelW*pixelS,fp);
    }
    fclose(fp);
}

void readBmpFromFile(char* path,BMP_FILE_HEADER * bmpFileHeader_p,BMP_INFO_HEADER * bmpInfoHeader_p,uint8_t ** dataPtr)
{
    FILE * fp = fopen(path,"rb");
    uint16_t bfType;  
    fread(&bfType,sizeof(bfType),1,fp);
    fread(bmpFileHeader_p,sizeof(BMP_FILE_HEADER),1,fp);
    fread(bmpInfoHeader_p,sizeof(BMP_INFO_HEADER),1,fp);
    size_t colorTableSize = bmpFileHeader_p->bfSize - bmpInfoHeader_p->biSizeImage -2 -sizeof(BMP_FILE_HEADER) - sizeof(BMP_INFO_HEADER);
    printf("colorTableSize=%d\n",colorTableSize);
    if(colorTableSize>0)
    {
        uint8_t * table = (uint8_t *)malloc(colorTableSize);
        fread(table,1,colorTableSize,fp);
        // for(int i=0;i<colorTableSize;i++)
        // {
        //     printf("colortable[%3d]: %3d\n",i,table[i]);
        // }
        printf("bfType: %d %d [%c%c] \n",bfType&0xff,bfType>>8,bfType&0xff,bfType>>8);
        uint32_t channel = bmpInfoHeader_p->biBitCount>>3;
        uint32_t raw_dataSize=bmpInfoHeader_p->biSizeImage;
        uint32_t raw_channel = channel;
        channel =3;
        uint32_t dataSize    =bmpInfoHeader_p->biWidth * bmpInfoHeader_p->biHeight * channel;
        *dataPtr=(uint8_t *)malloc(dataSize);
        uint8_t * raw=(uint8_t *)malloc(raw_dataSize);
        // fread(raw,sizeof(uint8_t),raw_dataSize,fp);
        for(int32_t i=0;i<bmpInfoHeader_p->biHeight;i++)
        {
            fread((raw) + (bmpInfoHeader_p->biHeight-i-1)*bmpInfoHeader_p->biWidth*raw_channel,sizeof(uint8_t),bmpInfoHeader_p->biWidth*raw_channel,fp);
        }
        BMP_COLOR_TBL * tbl_array = (BMP_COLOR_TBL*)table;


        for(int32_t i=0;i<bmpInfoHeader_p->biHeight;i++)
        {
            uint8_t * write_line_ptr = (*dataPtr) + (bmpInfoHeader_p->biHeight-i-1)*bmpInfoHeader_p->biWidth*channel;
            uint8_t * raw_line_ptr   = (raw) + (bmpInfoHeader_p->biHeight-i-1)*bmpInfoHeader_p->biWidth*raw_channel;
            for(int32_t j=0;j<bmpInfoHeader_p->biWidth;j++)
            {
                uint8_t v = raw_line_ptr[j];
                BMP_COLOR_TBL tbl_array_ = tbl_array[v];
                write_line_ptr[j*channel+0] = tbl_array_.B;
                write_line_ptr[j*channel+1] = tbl_array_.G;
                write_line_ptr[j*channel+2] = tbl_array_.R;
                
            }
            // fread((*dataPtr) + (bmpInfoHeader_p->biHeight-i-1)*bmpInfoHeader_p->biWidth*channel,sizeof(uint8_t),bmpInfoHeader_p->biWidth*channel,fp);
        }
        free(raw);
        bmpInfoHeader_p->biBitCount=channel<<3;
        bmpInfoHeader_p->biSizeImage = bmpInfoHeader_p->biWidth * bmpInfoHeader_p->biHeight * channel;
        free(table);
    }
    else
    {
    printf("bfType: %d %d [%c%c] \n",bfType&0xff,bfType>>8,bfType&0xff,bfType>>8);
    uint32_t channel = bmpInfoHeader_p->biBitCount>>3;
    uint32_t dataSize=bmpInfoHeader_p->biSizeImage;
    *dataPtr=(uint8_t *)malloc(dataSize);
    for(int32_t i=0;i<bmpInfoHeader_p->biHeight;i++)
    {
        fread((*dataPtr) + (bmpInfoHeader_p->biHeight-i-1)*bmpInfoHeader_p->biWidth*channel,sizeof(uint8_t),bmpInfoHeader_p->biWidth*channel,fp);
    }
    }
    fclose(fp);
}

void createBmpDataFromFile(BMP_DATA * bmp_data_p,char* path)
{
    // bmp_data_p = (BMP_DATA*)malloc(sizeof(BMP_DATA));
    bmp_data_p->dataPtr=0;
    readBmpFromFile(path,&bmp_data_p->bmpFileHeader,&bmp_data_p->bmpInfoHeader,&(bmp_data_p->dataPtr));
}

void releaseBmpData(BMP_DATA * bmp_data_p)
{
    if(((bmp_data_p)->dataPtr)!=0)
    {
        free((bmp_data_p)->dataPtr);
    }
}

size_t get_file_size(char *stream){
    size_t file_size = -1;
    struct stat buf;
    int fd;
    fd = open(stream, O_RDONLY);
    if(fstat(fd, &buf) == -1){
        printf("fstat failed :%s\n", strerror(errno));
        return -1;
    }
    else printf("size: %ld\n", buf.st_size);
    file_size = buf.st_size;
    return file_size;
}

void encodefile(char *filepath, char *outfilename){
    FILE *fp = fopen(filepath, "rb");
    uint16_t bfType;  
    BMP_FILE_HEADER bmpFileHeader_p;
    BMP_INFO_HEADER bmpInfoHeader_p;
    FILE *fp_t = fopen(outfilename, "wb");
    size_t size = get_file_size(filepath);
    size_t i = 0;
    uint8_t *dataPtr = (uint8_t *)malloc(size);
    uint8_t count = 1, current = 0;

    fread(&bfType,sizeof(bfType),1,fp);
    fread(&bmpFileHeader_p,sizeof(BMP_FILE_HEADER),1,fp);
    fread(&bmpInfoHeader_p,sizeof(BMP_INFO_HEADER),1,fp);
    size_t dataSize=bmpInfoHeader_p.biSizeImage;
    fread(dataPtr, sizeof(uint8_t), dataSize, fp);
    fwrite(&dataSize, sizeof(size_t), 1, fp_t);
    fwrite(&bfType,sizeof(bfType),1,fp_t);
    fwrite(&bmpFileHeader_p,sizeof(BMP_FILE_HEADER),1,fp_t);
    fwrite(&bmpInfoHeader_p,sizeof(BMP_INFO_HEADER),1,fp_t);
    current = dataPtr[0];
    for(i = 1;  i <= dataSize; i++){
        if(current == dataPtr[i]){
            count++;
            if(count == 255){
                fwrite(&current, sizeof(uint8_t), 1, fp_t);
                fwrite(&count, sizeof(uint8_t), 1, fp_t);
                count = 0;
            }
        }
        else{
            if(count != 0){
                fwrite(&current, sizeof(uint8_t), 1, fp_t);
                fwrite(&count, sizeof(uint8_t), 1, fp_t);
            }
            count = 1;
            current = dataPtr[i];
        }
    }
    if(count != 0){
        fwrite(&current, sizeof(uint8_t), 1, fp_t);
        fwrite(&count, sizeof(uint8_t), 1, fp_t);
    }

    fclose(fp);
    fclose(fp_t);
    free(dataPtr);
}

void decodefile(char *filepath, char *outfilename){
    FILE *fp = fopen(filepath, "rb");
    uint16_t bfType;  
    BMP_FILE_HEADER bmpFileHeader_p;
    BMP_INFO_HEADER bmpInfoHeader_p;
    FILE *fp_t = fopen(outfilename, "wb");
    size_t size = get_file_size(filepath);
    size_t orig_size = 0, i = 0;
    uint8_t *dataPtr = (uint8_t *)malloc(size);
    uint8_t count = 1, current = 0, n = 0;

    fread(&orig_size, sizeof(size_t), 1, fp);
    fread(&bfType,sizeof(bfType),1,fp);
    fread(&bmpFileHeader_p,sizeof(BMP_FILE_HEADER),1,fp);
    fread(&bmpInfoHeader_p,sizeof(BMP_INFO_HEADER),1,fp);
    fwrite(&bfType,sizeof(bfType),1,fp_t);
    fwrite(&bmpFileHeader_p,sizeof(BMP_FILE_HEADER),1,fp_t);
    fwrite(&bmpInfoHeader_p,sizeof(BMP_INFO_HEADER),1,fp_t);
    fread(dataPtr, sizeof(uint8_t), size - (sizeof(size_t) + sizeof(bfType) + sizeof(BMP_FILE_HEADER) + sizeof(BMP_INFO_HEADER)) / sizeof(uint8_t), fp);
    for(i = 0; i <= size - (sizeof(size_t) + sizeof(bfType) + sizeof(BMP_FILE_HEADER) + sizeof(BMP_INFO_HEADER)) / sizeof(uint8_t); i += 2){
        current = dataPtr[i];
        count = dataPtr[i + 1];
        for(n = count; n > 0; n--){
            fwrite(&current, sizeof(uint8_t), 1, fp_t);
        }
    }

    fclose(fp);
    fclose(fp_t);
    free(dataPtr);
}

void bgr8882bgr555(char * inBmpPath,char * outBmpPath)
{
    BMP_DATA  readBmp;
    createBmpDataFromFile(&readBmp,inBmpPath);
    uint32_t imgWidth  = (&readBmp)->bmpInfoHeader.biWidth;
    uint32_t imgHeight = (&readBmp)->bmpInfoHeader.biHeight;
    uint8_t *imgPtr    = (&readBmp)->dataPtr;
    uint32_t pixelS    = (&readBmp)->bmpInfoHeader.biBitCount>>3;
    //encode rgb888 into rgb565
    uint32_t rgb565_pixelS = 2;
    uint8_t * rgb565 = (uint8_t*) malloc(imgWidth*imgHeight*rgb565_pixelS);
    for(uint32_t i=0;i<imgHeight;i++)
    {
       for(uint32_t j=0;j<imgWidth;j++)
       {
         uint16_t B=imgPtr[i*imgWidth*pixelS+j*pixelS];
         uint16_t G=imgPtr[i*imgWidth*pixelS+j*pixelS+1];
         uint16_t R=imgPtr[i*imgWidth*pixelS+j*pixelS+2];
         *(uint16_t*)&rgb565[i*imgWidth*rgb565_pixelS+j*rgb565_pixelS]   = ((R<<7)&0x7c00) |  ((G<<2)&0x03e0) |  ((B>>3)&0x001f);
       } 
    }    
    saveBmpDataToFile(rgb565,imgWidth,imgHeight,rgb565_pixelS,outBmpPath);
    releaseBmpData(&readBmp);
    free(rgb565);
}

void bgr8882tbl256(char * inBmpPath,char * outBmpPath)
{
    // B2 G3 R3
    BMP_DATA  readBmp;
    createBmpDataFromFile(&readBmp,inBmpPath);
    uint32_t imgWidth  = (&readBmp)->bmpInfoHeader.biWidth;
    uint32_t imgHeight = (&readBmp)->bmpInfoHeader.biHeight;
    uint8_t *imgPtr    = (&readBmp)->dataPtr;
    uint32_t pixelS    = (&readBmp)->bmpInfoHeader.biBitCount>>3;
    uint8_t * newData  = (uint8_t*) malloc(imgWidth*imgHeight*1);
    uint8_t * colorTbl = (uint8_t*) malloc(256*sizeof(BMP_COLOR_TBL));
    BMP_COLOR_TBL * tbl = (BMP_COLOR_TBL*)colorTbl;
    for(uint32_t i=0;i<imgHeight;i++)
    {
       for(uint32_t j=0;j<imgWidth;j++)
       {
         uint8_t B=imgPtr[i*imgWidth*pixelS+j*pixelS];
         uint8_t G=imgPtr[i*imgWidth*pixelS+j*pixelS+1];
         uint8_t R=imgPtr[i*imgWidth*pixelS+j*pixelS+2];
         *(uint8_t*)&newData[i*imgWidth*1+j*1] = (B & 0xc0) | ((G >>2) & 0x38) | ((R>>5) & 0x07);
       } 
    }    
    for(int i=0;i<256;i++)
    {
        uint8_t b = ((i & 0xc0)>>6) * 255/4 ;
        uint8_t g = ((i & 0x38)>>3) * 255/8;
        uint8_t r = (i & 0x07) * 255/8;
        tbl[i].B  = b;
        tbl[i].G  = g;
        tbl[i].R  = r;
        tbl[i].A  = 0;
    }
    saveBmpDataToFile_colorTBL(newData,imgWidth,imgHeight,1,colorTbl,256*sizeof(BMP_COLOR_TBL),outBmpPath);
    releaseBmpData(&readBmp);
    free(colorTbl);

}

void bgr8882gray(char * inBmpPath,char * outBmpPath)
{
    BMP_DATA  readBmp;
    createBmpDataFromFile(&readBmp,inBmpPath);
    uint32_t imgWidth  = (&readBmp)->bmpInfoHeader.biWidth;
    uint32_t imgHeight = (&readBmp)->bmpInfoHeader.biHeight;
    uint8_t *imgPtr    = (&readBmp)->dataPtr;
    uint32_t pixelS    = (&readBmp)->bmpInfoHeader.biBitCount>>3;
    //uint32_t imgHin=0,imgWin=0;

    for(uint32_t i=0;i<imgHeight;i++)
    {
        //imgHin=i+1;
        for(uint32_t j=0;j<imgWidth*pixelS;j+=pixelS)
        {
            uint8_t gray=(uint8_t)((306**(imgPtr+i*imgWidth*pixelS+j+2)+601**(imgPtr+i*imgWidth*pixelS+j+1)+117**(imgPtr+i*imgWidth*pixelS+j))>>10);
            //uint8_t gray=(uint8_t)((*(imgPtr+i*imgWidth*pixelS+j+2)+*(imgPtr+i*imgWidth*pixelS+j+1)+*(imgPtr+i*imgWidth*pixelS+j))/3);
            //uint8_t gray=(uint8_t)(0.299**(imgPtr+i*imgWidth*pixelS+j+2)+0.587**(imgPtr+i*imgWidth*pixelS+j+1)+0.114**(imgPtr+i*imgWidth*pixelS+j));
            *(imgPtr+i*imgWidth*pixelS+j)=gray;
            *(imgPtr+i*imgWidth*pixelS+j+1)=gray;
            *(imgPtr+i*imgWidth*pixelS+j+2)=gray;
        }
    }

    saveBmpDataToFile(imgPtr,imgWidth,imgHeight,pixelS,outBmpPath);
    releaseBmpData(&readBmp);
}


int main(int argc, char * argv[]){
    if(argc < 2)
    {
        printf("error: usage =>  ./bmp_compress <c/d/e/f> <InputPath> <OutputPath>\n");
        printf("c/d: compress/decompress\n");
        printf("e/f/g: RGB888 to RGB555/TBL256/Gray\n");
        system("pause");
        return 0;
    }
    char * InputPath = argv[2];
    char * OutputPath = argv[3];
    if(strcmp(argv[1], "c") == 0){
        encodefile(InputPath, OutputPath);
    }
    else if(strcmp(argv[1], "d") == 0){
        decodefile(InputPath, OutputPath);
    }
    else if(strcmp(argv[1], "e") == 0){
        bgr8882bgr555(InputPath, OutputPath);
    }
    else if(strcmp(argv[1], "f") == 0){
        bgr8882tbl256(InputPath, OutputPath);
    }
    else if(strcmp(argv[1], "g") == 0){
        bgr8882gray(InputPath, OutputPath);
    }
    else{
        printf("Unkown Command.\n");
    }

        system("pause");
    return 0;
}
