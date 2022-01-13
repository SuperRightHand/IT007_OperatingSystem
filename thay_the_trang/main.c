#include<stdio.h>
#include<conio.h>
#include"functionsProcess.h"

void FIFOFunction(char Page_frames[], int Number_page) {
    // Tạo biến lưu độ dài của chuỗi tham chiếu
    int length_PageFrames = lengthArray(Page_frames);
    // Tạo mảng lưu lỗi khung trang
    int Page_Fault[20];
    // Tạo bảng lưu values của khung trang mỗi lần tham chiếu
    char Table_Page_Frames[20][20];
    // Reset values của bảng lưu các khung trang
    resetValueOfTable(Table_Page_Frames, length_PageFrames, Number_page);
    // Tạo mảng lưu bộ đếm(số lần lưu lại trên khung trang).
    int index_Page[20];
    //  Đặt giá trị bộ đếm(số lần lưu lại trên khung trang) về 0
    resetValueOfCount(index_Page, Number_page);
    for (int i = 0; i < length_PageFrames; i++)
    {
        countPage(index_Page, Number_page);
        if (checkValueinTable(Table_Page_Frames, Page_frames[i], Number_page, i))
        {
            int selection = selectRowChange(Page_frames, index_Page, Number_page);
            if (i != 0) pasteColumnToColumn(Table_Page_Frames, Number_page, i);
            Table_Page_Frames[selection][i] = Page_frames[i];
            index_Page[selection] = 0;
        }
        else pasteColumnToColumn(Table_Page_Frames, Number_page, i);
    }
    checkPageFault(Page_Fault, Table_Page_Frames, Number_page, length_PageFrames);
    displayScreen(Page_frames, Table_Page_Frames, Page_Fault, Number_page, length_PageFrames);
}

void OPTFunction(char Page_frames[], int Number_page) {
    // Tạo biến lưu độ dài của chuỗi tham chiếu
    int length_PageFrames = lengthArray(Page_frames);
    // Tạo mảng lưu lỗi khung trang
    int Page_Fault[20];
    // Tạo bảng lưu values của khung trang mỗi lần tham chiếu
    char Table_Page_Frames[20][20];
    // Reset values của bảng lưu các khung trang
    resetValueOfTable(Table_Page_Frames, length_PageFrames, Number_page);
    for (int i = 0; i < length_PageFrames; i++)
    {
        if (checkValueinTable(Table_Page_Frames, Page_frames[i], Number_page, i))
        {
            int selection = checkPositionValueinPageFrames(Table_Page_Frames, Page_frames, length_PageFrames, Number_page, i);
            if (i) pasteColumnToColumn(Table_Page_Frames, Number_page, i);
            Table_Page_Frames[selection][i] = Page_frames[i];
        }
        else pasteColumnToColumn(Table_Page_Frames, Number_page, i);
    }
    checkPageFault(Page_Fault, Table_Page_Frames, Number_page, length_PageFrames);
    displayScreen(Page_frames, Table_Page_Frames, Page_Fault, Number_page, length_PageFrames);
}

void LRUFunction(char Page_frames[], int Number_page) {
    // Tạo biến lưu độ dài của chuỗi tham chiếu
    int length_PageFrames = lengthArray(Page_frames);
    // Tạo mảng lưu lỗi khung trang
    int Page_Fault[20];
    // Tạo bảng lưu values của khung trang mỗi lần tham chiếu
    char Table_Page_Frames[20][20];
    // Reset values của bảng lưu các khung trang
    resetValueOfTable(Table_Page_Frames, length_PageFrames, Number_page);
    // Tạo mảng lưu bộ đếm(số lần lưu lại trên khung trang).
    int index_Page[20];
    //  Đặt giá trị bộ đếm(số lần lưu lại trên khung trang) về 0
    resetValueOfCount(index_Page, Number_page);
    for (int i = 0; i < length_PageFrames; i++)
    {
        countPage(index_Page, Number_page);
        if (checkValueinTable(Table_Page_Frames, Page_frames[i], Number_page, i))
        {
            int selection = selectRowChange(Page_frames, index_Page, Number_page);
            if (i != 0) pasteColumnToColumn(Table_Page_Frames, Number_page, i);
            Table_Page_Frames[selection][i] = Page_frames[i];
            index_Page[selection] = 0;
        }
        else
        {
            int selection = checkPositionValueinTable(Table_Page_Frames, Page_frames[i], Number_page, i);
            index_Page[selection] = 0;
            pasteColumnToColumn(Table_Page_Frames, Number_page, i);
        }
    }
    checkPageFault(Page_Fault, Table_Page_Frames, Number_page, length_PageFrames);
    displayScreen(Page_frames, Table_Page_Frames, Page_Fault, Number_page, length_PageFrames);
}

void displayMenu(char Page_frames[]) {
    printf("\n\t--- Page Replacement algorithm ---");
    printf("\n\t1. Default referenced sequence");
    printf("\n\t2. Manual input sequence");
    printf("\n\tPress number to choose");
    char n;
    n = _getch();
    switch (n)
    {
    case '1':
        Page_frames[0]= '2';
        Page_frames[1]= '0';
        Page_frames[2]= '5';
        Page_frames[3]= '2';
        Page_frames[4]= '2';
        Page_frames[5]= '0';
        Page_frames[6]= '9';
        Page_frames[7]= '7';
        Page_frames[8]= '0';
        Page_frames[9]= '0';
        Page_frames[10]= '7';
        break;
    case '2':
        printf("\n\t--- Page Replacement algorithm ---");
        printf("\nInput sequence: ");
        gets(Page_frames);
        break;
    default:
        break;
    }
}

void displayInputFrames(int* Number_page) {
    printf("\n\t--- Page Replacement algorithm ---");
    printf("\nInput page frames: ");
    scanf("%d", Number_page);
}

void displayOption(char Page_frames[], int Number_page) {
    printf("\n\t--- Page Replacement algorithm ---");
    printf("\n1. FIFO algorithm");
    printf("\n2. OPT algorithm");
    printf("\n3. LRU algorithm");
    printf("\nPress number to choose");
    char x;
    x = getch();
    switch (x)
    {
    case '1':
        FIFOFunction(Page_frames, Number_page);
        break;
    case '2':
        OPTFunction(Page_frames, Number_page);
        break;
    case '3':
        LRUFunction(Page_frames, Number_page);
        break;
    default:
        break;
    }
}

int main() {
    // Tạo biến chuỗi tham chiếu
    char Page_frames[20];
    // Reset values chuỗi tham chiếu
    resetValueOfPageFrams(Page_frames);
    // Tạo biến số khung trang
    int Number_page;
    // Giao diện khởi tạo chuỗi tham chiếu
    displayMenu(Page_frames);
    // Giao diện nạp số khung trang
    displayInputFrames(&Number_page);
    // Giao diện chọn thuật toán thay trang
    displayOption(Page_frames, Number_page);
}