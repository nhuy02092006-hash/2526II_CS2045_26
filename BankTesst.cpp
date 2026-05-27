#include <iostream>
#include <vector>
#include <string>

using namespace std;

string evaluate_loan(int age, double income, int credit_score, char employment)
{
    if (age < 18 || age > 65)
        return "Invalid Input";

    if (income < 5.0 || income > 500.0)
        return "Invalid Input";

    if (credit_score < 300 || credit_score > 850)
        return "Invalid Input";

    if (employment != 'C' && employment != 'F')
        return "Invalid Input";

    string risk;

    if (credit_score >= 300 && credit_score <= 500)
        risk = "High";
    else if (credit_score >= 501 && credit_score <= 700)
        risk = "Medium";
    else
        risk = "Low";

    if (risk == "High")
        return "REJECT";

    if (income < 15.0)
    {
        if (employment == 'C' && risk == "Low")
            return "MANUAL REVIEW";
        else
            return "REJECT";
    }

    if (employment == 'C')
        return "APPROVE";

    return "MANUAL REVIEW";
}

struct TestCase
{
    int age;
    double income;
    int credit_score;
    char employment;
    string expected;
};

int main()
{
    vector<TestCase> tests = {
        {17,20.0,600,'C',"Invalid Input"},
        {66,20.0,600,'C',"Invalid Input"},
        {30,4.9,600,'C',"Invalid Input"},
        {30,500.1,600,'C',"Invalid Input"},
        {30,20.0,299,'C',"Invalid Input"},
        {30,20.0,851,'C',"Invalid Input"},
        {30,20.0,600,'X',"Invalid Input"},

        {18,5.0,300,'C',"REJECT"},
        {65,500.0,850,'C',"APPROVE"},
        {19,5.1,301,'F',"REJECT"},
        {64,499.9,849,'F',"MANUAL REVIEW"},

        {30,100.0,500,'C',"REJECT"},
        {30,100.0,400,'F',"REJECT"},

        {30,14.9,701,'C',"MANUAL REVIEW"},

        {30,14.9,650,'C',"REJECT"},
        {30,14.9,750,'F',"REJECT"},

        {30,15.0,650,'C',"APPROVE"},
        {30,100.0,701,'C',"APPROVE"},

        {30,15.0,650,'F',"MANUAL REVIEW"},
        {30,100.0,750,'F',"MANUAL REVIEW"}
    };

    int passed = 0;

    for (int i = 0; i < tests.size(); i++)
    {
        string result = evaluate_loan(
            tests[i].age,
            tests[i].income,
            tests[i].credit_score,
            tests[i].employment
        );

        if (result == tests[i].expected)
        {
            passed++;
            cout << "TC" << i + 1 << ": PASS" << endl;
        }
        else
        {
            cout << "TC" << i + 1
                 << ": FAIL"
                 << " | Expected = " << tests[i].expected
                 << " | Got = " << result
                 << endl;
        }
    }

    cout << endl;
    cout << "Passed "
         << passed
         << "/"
         << tests.size()
         << " test cases"
         << endl;

    return 0;
}
