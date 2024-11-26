#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <fstream> 

using namespace std;

enum Speciality { ITIS, RE, KN, KI, PZ };
string speciality_str[] = { "Інформатика", "Радіоелектроніка", "Комп'ютерні науки", "Комп'ютерна інженерія", "Програмне забезпечення" };

struct Students
{
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    int grade_info;
};

void Create(Students* S, const int N);
void CountStudentsWithoutThrees(Students* S, int N, int& count);
double PercentageLowAverage(Students* S, const int N);
void Print(Students* S, const int N);
void SaveToBinaryFile(Students* S, const int N, const string& filename);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: "; cin >> N;

    Students* S = new Students[N];

    Create(S, N);
    Print(S, N);

    int count_without_threes = 0;
    CountStudentsWithoutThrees(S, N, count_without_threes);

    cout << "Кількість студентів, які вчаться без трійок: " << count_without_threes << endl;
    cout << "Процент студентів, середній бал яких менший за 4: " << setprecision(2) << fixed << PercentageLowAverage(S, N) << "%" << endl;

    // Записуємо в бінарний файл
    SaveToBinaryFile(S, N, "bbb.dat");

    delete[] S;
    return 0;
}

void Create(Students* S, const int N)
{
    for (int i = 0; i < N; i++)
    {
        int speciality;
        cout << "Номер студента: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "Прізвище: "; getline(cin, S[i].surname); cout << endl;
        cout << "Курс: "; cin >> S[i].course; cout << endl;
        cout << "Спеціальність (0 - Інформатика, 1 - Радіоелектроніка, 2 - Комп'ютерні науки," << endl;
        cout << "3 - Комп'ютерна інженерія, 4 - Програмне забезпечення): ";
        cin >> speciality;
        S[i].speciality = (Speciality)speciality;
        cout << "Оцінка з фізики: "; cin >> S[i].grade_physics; cout << endl;
        cout << "Оцінка з математики: "; cin >> S[i].grade_math; cout << endl;
        cout << "Оцінка з інформатики: "; cin >> S[i].grade_info; cout << endl;
        cout << endl;
    }
}

void CountStudentsWithoutThrees(Students* S, int N, int& count)
{
    count = 0;
    for (int i = 0; i < N; i++)
    {
        if (S[i].grade_physics > 3 && S[i].grade_math > 3 && S[i].grade_info > 3)
        {
            count++;
        }
    }
}

double PercentageLowAverage(Students* S, const int N)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        double average = (S[i].grade_physics + S[i].grade_math + S[i].grade_info) / 3.0;
        if (average < 4)
        {
            count++;
        }
    }
    return count * 100.0 / N;
}

void Print(Students* S, const int N)
{
    cout << "=================================================================================================" << endl;
    cout << "|  №  |   Прізвище   |  Курс  |     Спеціальність     |  Фізика  |  Математика  |  Інформатика  |" << endl;
    cout << "-------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(4) << left << i + 1 << " ";
        cout << "|" << setw(14) << left << S[i].surname;
        cout << "|" << setw(8) << left << S[i].course;
        cout << "|" << setw(23) << left << speciality_str[S[i].speciality];
        cout << "|" << setw(10) << left << S[i].grade_physics;
        cout << "|" << setw(14) << left << S[i].grade_math;
        cout << "|" << setw(15) << left << S[i].grade_info << "|" << endl;
    }
    cout << "=================================================================================================" << endl << endl;
}

void SaveToBinaryFile(Students* S, const int N, const string& filename)
{
    ofstream outFile(filename, ios::binary); // Відкриваємо файл для запису в бінарному режимі
    if (!outFile)
    {
        cout << "Не вдалося відкрити файл для запису!" << endl;
        return;
    }

    for (int i = 0; i < N; i++)
    {
        // Записуємо довжину та вміст прізвища
        size_t surname_length = S[i].surname.size();
        outFile.write(reinterpret_cast<char*>(&surname_length), sizeof(surname_length)); 
        outFile.write(S[i].surname.c_str(), surname_length); 

        
        outFile.write(reinterpret_cast<char*>(&S[i].course), sizeof(S[i].course));
        outFile.write(reinterpret_cast<char*>(&S[i].speciality), sizeof(S[i].speciality));
        outFile.write(reinterpret_cast<char*>(&S[i].grade_physics), sizeof(S[i].grade_physics));
        outFile.write(reinterpret_cast<char*>(&S[i].grade_math), sizeof(S[i].grade_math));
        outFile.write(reinterpret_cast<char*>(&S[i].grade_info), sizeof(S[i].grade_info));
    }

    outFile.close(); 
    cout << "Дані успішно записані в файл " << filename << endl;
}
