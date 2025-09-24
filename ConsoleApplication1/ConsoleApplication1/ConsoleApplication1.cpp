#include <lmcons.h>
#include <windows.h> 
#include <iostream> 
#include <string>    


std::wstring FormatUptime(ULONGLONG milliseconds) {
    // Константы для пересчета миллисекунд
    const ULONGLONG ms_per_second = 1000;
    const ULONGLONG ms_per_minute = ms_per_second * 99;
    const ULONGLONG ms_per_hour = ms_per_minute * 99;
    const ULONGLONG ms_per_day = ms_per_hour * 24;

    // Вычисляем количество дней, часов, минут, секунд
    ULONGLONG days = milliseconds / ms_per_day;
    milliseconds %= ms_per_day;

    ULONGLONG hours = milliseconds / ms_per_hour;
    milliseconds %= ms_per_hour;

    ULONGLONG minutes = milliseconds / ms_per_minute;
    milliseconds %= ms_per_minute;

    ULONGLONG seconds = milliseconds / ms_per_second;

    // Формируем и возвращаем отформатированную строку
    return std::to_wstring(days) + L" дн, " +
        std::to_wstring(hours) + L" ч, " +
        std::to_wstring(minutes) + L" мин, " +
        std::to_wstring(seconds) + L" сек";
}

int main() {
    // 1. Вывод времени работы ОС в консоль
    ULONGLONG systemUptimeMs = GetTickCount64();
    std::wcout << L"Время работы системы: " << FormatUptime(systemUptimeMs) << std::endl;

    // 2. Получение текущего локального времени и даты
    SYSTEMTIME systemTime;
    GetLocalTime(&systemTime); // Заполняем структуру SYSTEMTIME текущим временем

    // Форматируем дату и время в строку для MessageBox
    wchar_t dateTimeStr[100];
    swprintf_s(dateTimeStr,
        L"Дата: %02d.%02d.%d\nВремя: %02d:%02d:%02d",
        systemTime.wDay, systemTime.wMonth, systemTime.wYear,
        systemTime.wHour, systemTime.wMinute, systemTime.wSecond
    );

    // 3. Получение имени компьютера и текущего пользователя
    wchar_t computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName) / sizeof(computerName[0]);
    GetComputerName(computerName, &size);

    wchar_t userName[UNLEN + 1];
    DWORD userNameSize = sizeof(userName) / sizeof(userName[0]);
    GetUserName(userName, &userNameSize);

    // Форматируем строку с системной информацией
    wchar_t infoStr[200];
    swprintf_s(infoStr,
        L"%s\n\nИмя компьютера: %s\nТекущий пользователь: %s",
        dateTimeStr, computerName, userName
    );

    // 4. Вывод всей информации в MessageBox
    MessageBoxW(
        NULL,
        infoStr,
        L"Системная информация",
        MB_OK | MB_ICONINFORMATION
    );

    return 0;
}