#include<stdio.h>
#include<conio.h>

#define Default_Length 20


void displayScreen(char Page_frames[], char Table_Page_Frames[Default_Length][Default_Length], int Page_Fault[], int Number_page, int length_PageFrames) {
    // Hàm xuất ra màn hình
    printf("\n");
    for (int i = 0; i < length_PageFrames; i++)
    {
        printf("%c ", Page_frames[i]);
    }
    for (int i = 0; i < Number_page; i++)
    {
        printf("\n");
        for (int j = 0; j < length_PageFrames; j++)
        {
            printf("%c", Table_Page_Frames[i][j]);
            printf(" ");
        }
    }
    printf("\n");
    int index = 0;
    for (int i = 0; i < length_PageFrames; i++)
    {
        index+=Page_Fault[i];
        if (Page_Fault[i]) printf("* ");
        else printf("  ");
    }
    printf("\nNumber of Page Fault: %d", index);
}

void checkPageFault(int Page_Fault[],char Table_Page_Frames[][Default_Length], int Rows, int Columns) {
    // Hàm kiểm tra lỗi trang
    Page_Fault[0] = 1;
    for (int i = 1; i < Columns; i++)
    {
        for (int j = 0; j < Rows; j++)
        {
            if (Table_Page_Frames[j][i] != Table_Page_Frames[j][i-1])
            {
                Page_Fault[i] = 1;
                break;
            }
            Page_Fault[i] = 0;
        }
    }
}

void countPage(int index_Page[], int Number_page) {
    // Hàm đếm số lần lưu lại trên khung trang
    for (int i = 0; i < Number_page; i++)
    {
        index_Page[i]++;
    }
}

void resetValueOfCount(int A[], int length) {
    // Hàm đặt giá trị bộ đếm(số lần lưu lại trên khung trang) về 0
    for (int i = 0; i < length; i++)
    {
        A[i] = 0;
    }
}

void resetValueOfPageFrams(char A[]) {
    // Hàm reset values chuỗi tham chiếu
    for (int i = 0; i < Default_Length; i++)
    {
        A[i] = ' ';
    }
}

int lengthArray(char Page_frames[]) {
    // Hàm tính độ dài thật sự của một mảng
    int index = 0;
    while (Page_frames[index] != '\0' && Page_frames[index] != ' ') index++;
    return index;
}

void resetValueOfTable(char A[][Default_Length], int Rows, int Columns) {
    //  Hàm reset values của bảng lưu các khung trang
    for (int i = 0; i < Rows; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            A[i][j] = ' ';
        }
    }
}

int selectRowChange(char Page_frames[], int index_Page[], int Number_page) {
    // Hàm chọn vị trí trong khung trang sẽ bị thay trong thuật toán FIFO và LRU
    int max = index_Page[0];
    int selection = 0;
    for (int i = 0; i < Number_page; i++)
    {
        if (index_Page[i] > max)
        {
            max = index_Page[i];
            selection = i;
        }
    }
    return selection;
}

int checkValueinTable(char Table_Page_Frames[][Default_Length], char Page, int Number_page, int Columns_Frames_Current) {
    // Hàm kiểm tra kiểm tra giá trị tham chiếu có nằm sẵn trong khung trang hay không.
    if (Columns_Frames_Current)
    {
        for (int i = 0; i < Number_page; i++)
        {
            if (Table_Page_Frames[i][Columns_Frames_Current-1] == Page) return 0;
        }
    }
    return 1;
}

void pasteColumnToColumn(char Table_Page_Frames[][Default_Length], int Number_page, int column_Current) {
    // Hàm sao lưu values của khung trang lên bảng lưu đã tạo trước đó.
    for (int i = 0; i < Number_page; i++)
    {
        Table_Page_Frames[i][column_Current] = Table_Page_Frames[i][column_Current-1];
    }
}

int checkPositionValueinTable(char Table_Page_Frames[][Default_Length], char Page, int Number_page, int Columns_Frames_Current) {
    // Hàm xác định vị trí lúc giá trị của chuỗi tham chiếu có sẵn trong khung trang
    if (Columns_Frames_Current)
    {
        for (int i = 0; i < Number_page; i++)
        {
            if (Table_Page_Frames[i][Columns_Frames_Current-1] == Page) return i;
        }
    }
}

int checkPositionValueinPageFrames(char Table_Page_Frames[][Default_Length], char Page_frames[], int length_PageFrames, int Number_page, int column_Current) {
    //  Hàm chọn vị trí trong khung trang sẽ bị thay trong thuật toán OPT
    int index_Max = 0;
    int selection = 0;
    if (column_Current)
    {
        for (int i = 0; i < Number_page; i++)
        {
            for (int j = column_Current + 1; j < length_PageFrames; j++)
            {
                if (Page_frames[j] == Table_Page_Frames[i][column_Current - 1])
                {
                    if (j > index_Max)
                    {
                        index_Max = j;
                        selection = i;
                    }
                    break;
                }
                if (j == length_PageFrames - 1) index_Max = 0;
            }
            if (index_Max == 0)
            {
                selection = i;
                break;
            }

        }
        for (int i = 0; i < Number_page; i++)
        {
            if (Table_Page_Frames[i][column_Current - 1] == ' ')
            {
                selection = i;
                break;
            }
        }
    }
    return selection;
}