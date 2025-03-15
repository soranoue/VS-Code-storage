#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define PAGE_FILE_SIZE 255

typedef struct _FSFile_
{
    uint8_t page_number;
    uint8_t file[PAGE_FILE_SIZE];
}FSFile;

/* Maximum length of the names in the file system, including th extension */
#define NAME_MAX_LEN 16
/* Type for table entry */
typedef struct _FileEntry_
{
    /* Bit 0: 1 = directory, 0 = file
     * bit n: reserved
     * Bit 7: 1 = occupied, 0 = free */
    uint8_t flags;
    char name[NAME_MAX_LEN];
    uint8_t start_page;
    /* Size of the file in bytes, little-endian! */
    uint16_t size;
    /* date format (BCD) */
    uint8_t  year[2];
    uint8_t  month;
    uint8_t  day;
    uint8_t  date;
    uint8_t  hours;
    uint8_t  minutes;
    uint8_t  seconds;
    uint8_t reserved[4];
}FileEntry;

#define PAGE_DIR_NUM 8

typedef struct _FSDir_
{
    FileEntry entry[PAGE_DIR_NUM];
}FSDir;

#define BITMAP_SIZE 32
#define RESERVED_SIZE 28
#define HEADER_ENTRY_NUM 6
/* Type for partition header */
typedef struct _FSHeader_
{
  uint8_t magic;    /* Must be 'Z' ascii code */
  uint8_t version;  /* Version of the file system */
  /* Number of bytes composing the bitmap.
   * No matter how big the disk actually is, the bitmap is always
   * BITMAP_SIZE bytes big, thus we need field to mark the actual
   * number of bytes we will be using. */
  uint8_t bitmap_size;
  /* Number of free pages */
  uint8_t free_pages;
  /* Bitmap for the free pages. A used page is marked as 1, else 0 */
  uint8_t pages_bitmap[BITMAP_SIZE];   /* 256 pages/8-bit = 32 */
  /* Reserved bytes, to align the entries and for future use, such as
   * extended root directory, volume name, extra bitmap, etc... */
  uint8_t reserved[RESERVED_SIZE];
  /* Root directory, must be at an offset multiple of sizeof(FileEntry) */
  FileEntry entries[HEADER_ENTRY_NUM];
}FSHeader;

/**
 * Help that converting an 8-bit BCD value into a binary value.
 */
static inline int fromBCD(uint8_t value) {
    return (value >> 4) * 10 + (value & 0xf);
}

/**
 * Convert a value between 0 and 99 into a BCD values.
 * For example, if `value` is 13, this function returns 0x13 (in hex!)
 */
static inline uint8_t toBCD(int value) {
    return (((value / 10) % 10) << 4) | (value % 10);
}

/**
 * @brief Allocate one page in the given header's bitmap.
 *
 * @param header File system header to allocate the page from.
 *
 * @return Page number on success, 0 on error.
 */
static uint8_t allocatePage(FSHeader* header) 
{
  const int size = header->bitmap_size;
  int i = 0;
  uint8_t value = 0;
  for (i = 0; i < size; i++) {
    value = header->pages_bitmap[i];
    if (value != 0xff) {
      break;
    }
  }
  /* If we've reached the size, the bitmap is full */
  if (i == size) {
    return 0;
  }
  /* Else, return the index */
  int index_0 = 0;
  while ((value & 1) != 0) {
    value >>= 1;
    index_0++;
  }

  /* Set the page as allocated in the bitmap */
  header->pages_bitmap[i] |= 1 << index_0;
  header->free_pages--;
  return i * 8 + index_0;
}

static void fs_create_image(char *FileName)
{
    FILE *fp = fopen(FileName, "wb+");
    //fopen_s(fp, FileName, "wb+");
    uint8_t blank = NULL;
    fwrite(&blank, sizeof(blank), 65536, fp);
    fclose(fp);
}

static void fs_format(char *FileName, uint8_t mode)
{
    FSHeader header;
    int i;
    uint8_t blank = NULL;
    header.magic = 'Z';
    header.version = 1;
    header.bitmap_size = BITMAP_SIZE;
    header.free_pages = PAGE_FILE_SIZE;
    for(i = 0; i < BITMAP_SIZE; i++) {
        header.pages_bitmap[i] = 0x00;
    }
    for(i = 0; i < HEADER_ENTRY_NUM; i++) {
        header.entries->flags = 0x00;
    }

    FILE *fp = fopen(FileName, "wb+");
    //fopen_s(fp, FileName, "wb+");
    fwrite(&header, sizeof(header), 1, fp);
    if(mode == 1) {
        fwrite(&blank, sizeof(blank), 64512, fp);
    }
    fclose(fp);
}

void main()
{
    //char FileName = "114514.bin";
    fs_create_image("114514.bin");
    fs_format("114514.bin", 1);
}
