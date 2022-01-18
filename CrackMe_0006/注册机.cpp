// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <windows.h>
#include <iostream>

int main()
{
    DWORD c_serial_number = 0;
    DWORD d_serial_number = 0;

    GetVolumeInformationA("c:\\", NULL, 0, &c_serial_number, NULL , NULL, NULL, 80);
    GetVolumeInformationA("d:\\", NULL, 0, &d_serial_number, NULL, NULL, NULL, 80);

    printf("C盘序列号：%x\n", c_serial_number);
    printf("D盘序列号：%x\n", d_serial_number);

    int magic_number = (int)(sqrt(pow((double)c_serial_number,2) + pow((double)d_serial_number, 2)));
    printf("根据磁盘序列号得出magic_number：%X\n",magic_number);

    char username[255] = { 0 };
    long long username_mul = 1;

    printf("请输入用户名（大于4位小于50位）：");
    scanf_s("%s",username,255);
    
    //计算magic_number
    for (int i = 0; i < strlen(username);i++) 
        username_mul *= username[i];

    unsigned int username_mul_word = (unsigned int)((0xFFFFFFFF) & username_mul) + (unsigned int)(((0xFFFFFFFF00000000) & username_mul) >> 32);
    //自实现循环左移
    username_mul_word = ((username_mul_word << 1) | (username_mul_word >> 31));
    
    int index_key = (username_mul_word | magic_number) & 0x0FFFFFFF;

    char dict[] = "071362de9f8ab45c";
    char serial[16] = {0};
    //每次以key % 16为索引在dic中取值，循环直至key / 4为0为止。
    int i = 0;
    bool exit_flag = false;
    while (!exit_flag){
        serial[i] = dict[index_key % 16];
        if (!(index_key / 0x4)) exit_flag = true;
        index_key = index_key / 0x4;
        i += 1;
    }

    printf("您输入的用户名注册码计算结果为：%s\n", serial);
}
