#include <iostream>
#include <cctype>    
#include <cwctype>   
#include <cstring>   
#include <cwchar>    
#include <windows.h> 


int countwords(const char* str) {
    if (str == nullptr || *str == '\0') {
        return 0;
    }

    int count = 0;
    bool inWord = false;

    while (*str) {
        // Проверяем, является ли символ буквой или цифрой
        if (std::isalpha(static_cast<unsigned char>(*str)) ||
            std::isdigit(static_cast<unsigned char>(*str))) {
            if (!inWord) {
                count++;
                inWord = true;
            }
        }
        else {
            // Любой не-буквенный символ считается разделителем
            inWord = false;
        }
        str++;
    }

    return count;
}

void reversestring(char* str) {
    if (str == nullptr || *str == '\0') {
        return;
    }

    char* start = str;
    char* end = str + std::strlen(str) - 1;

    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}

BOOL isstringpalindrome(const char* str) {
    if (str == nullptr || *str == '\0') {
        return TRUE;
    }

    const char* left = str;
    const char* right = str + std::strlen(str) - 1;

    while (left < right) {
        // Пропускаем не-буквенные символы слева
        while (left < right && !std::isalpha(static_cast<unsigned char>(*left))) {
            left++;
        }

        // Пропускаем не-буквенные символы справа
        while (left < right && !std::isalpha(static_cast<unsigned char>(*right))) {
            right--;
        }

        if (left >= right) {
            break;
        }

        // Сравниваем символы без учета регистра
        if (std::tolower(static_cast<unsigned char>(*left)) !=
            std::tolower(static_cast<unsigned char>(*right))) {
            return FALSE;
        }

        left++;
        right--;
    }

    return TRUE;
}


int countwords(const wchar_t* str) {
    if (str == nullptr || *str == L'\0') {
        return 0;
    }

    int count = 0;
    bool inWord = false;

    while (*str) {
        if (std::iswalpha(*str) || std::iswdigit(*str)) {
            if (!inWord) {
                count++;
                inWord = true;
            }
        }
        else {
            inWord = false;
        }
        str++;
    }

    return count;
}

void reversestring(wchar_t* str) {
    if (str == nullptr || *str == L'\0') {
        return;
    }

    wchar_t* start = str;
    wchar_t* end = str + std::wcslen(str) - 1;

    while (start < end) {
        wchar_t temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}

BOOL isstringpalindrome(const wchar_t* str) {
    if (str == nullptr || *str == L'\0') {
        return TRUE;
    }

    const wchar_t* left = str;
    const wchar_t* right = str + std::wcslen(str) - 1;

    while (left < right) {
        while (left < right && !std::iswalpha(*left)) {
            left++;
        }

        while (left < right && !std::iswalpha(*right)) {
            right--;
        }

        if (left >= right) {
            break;
        }

        if (std::towlower(*left) != std::towlower(*right)) {
            return FALSE;
        }

        left++;
        right--;
    }

    return TRUE;
}


int main() {
    // Тестирование ANSI-функций
    std::cout << "ANSI functions test:" << std::endl;

    const char* ansiText = "Hello, World! This is a test string.";
    char ansiBuffer[100];

    // Безопасное копирование строки
    strcpy_s(ansiBuffer, sizeof(ansiBuffer), ansiText);

    std::cout << "Original: " << ansiBuffer << std::endl;
    std::cout << "Word count: " << countwords(ansiBuffer) << std::endl;

    reversestring(ansiBuffer);
    std::cout << "Reversed: " << ansiBuffer << std::endl;

    const char* palindrome = "A man, a plan, a canal, Panama!";
    std::cout << "Is palindrome '" << palindrome << "': "
        << (isstringpalindrome(palindrome) ? "YES" : "NO") << std::endl;

    std::cout << std::endl;

    // Тестирование Unicode-функций
    std::wcout << L"Unicode functions test:" << std::endl;

    const wchar_t* unicodeText = L"Привет, Мир! Это тестовая строка.";
    wchar_t unicodeBuffer[100];

    // Безопасное копирование широкой строки
    wcscpy_s(unicodeBuffer, sizeof(unicodeBuffer) / sizeof(wchar_t), unicodeText);

    std::wcout << L"Original: " << unicodeBuffer << std::endl;
    std::wcout << L"Word count: " << countwords(unicodeBuffer) << std::endl;

    reversestring(unicodeBuffer);
    std::wcout << L"Reversed: " << unicodeBuffer << std::endl;

    const wchar_t* unicodePalindrome = L"А роза упала на лапу Азора";
    std::wcout << L"Is palindrome '" << unicodePalindrome << L"': "
        << (isstringpalindrome(unicodePalindrome) ? L"YES" : L"NO") << std::endl;

    return 0;
}