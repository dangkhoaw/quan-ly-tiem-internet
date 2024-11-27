#include "../include/console.hpp"
#include <iostream>

namespace ConsoleUtils
{
    /// @brief Hiển thị hoặc ẩn con trỏ nhấp nháy
    /// @param CursorVisibility True: Hiển thị, False: Ẩn
    void ShowCursor(bool CursorVisibility)
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
        SetConsoleCursorInfo(handle, &cursor);
    }

    /// @brief Di chuyển con trỏ đến vị trí (posX, posY)
    void Gotoxy(SHORT posX, SHORT posY)
    {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD Position;
        Position.X = posX;
        Position.Y = posY;

        SetConsoleCursorPosition(hStdout, Position);
    }

    /// @brief Xóa dòng
    void ClearLine(SHORT posY)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        Gotoxy(0, posY);
        for (int i = 0; i < consoleWidth; i++)
        {
            std::cout << " ";
        }
        Gotoxy(0, posY);
    }

    /// @brief Xóa từ vị trí (posX, posY) với length ký tự
    void ClearLine(SHORT posX, SHORT posY, SHORT length)
    {
        Gotoxy(posX, posY);
        for (int i = 0; i < length; i++)
        {
            std::cout << " ";
        }
        Gotoxy(posX, posY);
    }
}