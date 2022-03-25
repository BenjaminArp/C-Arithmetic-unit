#include <stdio.h>
#include <stdint.h>

#define DEF_LEN 64*3

void Int64ToBinary(int64_t i64, int* a);
void AddBinary(int* a, int* b, int* res);
void ShiftBinaryToLeft(int* a, int nShift, int* res);
void MultiplyBinary(int* a, int* b, int* res);
void DebugOutput(const char* sz, int* a);
void BinaryComplement(int *a, int* res);
int BinaryToInt(int* a);

int main()
{
    int i,j;
    int negative[3] = { 0, 0, 0 };
    int binaryInput[3][DEF_LEN];
    int squared[3][DEF_LEN];
    int cubed[3][DEF_LEN];
    int res[3][DEF_LEN];
    //Numbers which solve the problem x^3+y^3+z^3 = 42
    int64_t input[3] = { -80538738812075974, 80435758145817515, 12602123297335631 };

    for (i = 0; i < 3; i++)
    {
        // Complement if negative
        if (input[i] < 0) {
            input[i] = -input[i];
            negative[i] = 1;
        }
        // Convert to binary
        Int64ToBinary(input[i], binaryInput[i]);
        // Debug output
        DebugOutput("Input ", binaryInput[i]);

        // Square binary
        MultiplyBinary(binaryInput[i], binaryInput[i], squared[i]);
        DebugOutput("Squared ", squared[i]);
        // Cube binary
        MultiplyBinary(squared[i], binaryInput[i], cubed[i]);
        DebugOutput("Cubed ", cubed[i]);

        // Complement of Cubed if input negative
        if(negative[i])
        {
            BinaryComplement(cubed[i], res[i]);
            for(j = 0; j < DEF_LEN; j++){
                cubed[i][j] = res[i][j];
            }
        }
    }

    // Add all three cubed values
    int intermediateSum[DEF_LEN];
    int sum[DEF_LEN];

    AddBinary(cubed[0], cubed[1], intermediateSum);
    AddBinary(intermediateSum, cubed[2], sum);

    // Debug output
    DebugOutput("sum ", sum);

    // Convert to Decimal
    int result = BinaryToInt(sum);

    printf("%d",result);

    return 0;
}

void Int64ToBinary(int64_t i64, int* a)
{
    int i;
    // convert decimal number to bit array
    for (i = 0; i < DEF_LEN; i++)
    {
        a[i] = (i64 % 2);
        i64 >>= 1; // i64 = i64 >> 1
    }
}

void AddBinary(int* a, int* b, int* res)
{
    int i;
    // set result to 0
    for ( i = 0; i < DEF_LEN; i++)
        res[i] = 0;
    // now add and fill result
    int nCarryOver = 0;
    for (i = 0; i < DEF_LEN; i++)
    {
        res[i] = a[i] + b[i] + nCarryOver;

        if (res[i] > 1 /*&& i < DEF_LEN - 1*/){    // carryover?
            nCarryOver = 1;
            res[i] -= 2;
        } else {
            nCarryOver = 0;
        }
    }
    if (nCarryOver) {

    }
}

void ShiftBinaryToLeft(int* a, int nShift, int* res)
{
    int i;
    // set result to 0
    for (i = 0; i < DEF_LEN; i++)
        res[i] = 0;

    // shift
    for (i = nShift; i < DEF_LEN; i++)
        res[i] = a[i - nShift];
}

void MultiplyBinary(int* a, int* b, int* res)
{
    int tmpShift[DEF_LEN];
    int tmpRes[DEF_LEN];
    int i,j;

    // set result to 0
    for (i = 0; i < DEF_LEN; i++)
        res[i] = 0;

    for (i = 0; i < DEF_LEN; i++)
    {
        if (!b[i])  // ignore 0
            continue;
        // so b[i] is 1
        ShiftBinaryToLeft(a, i, tmpShift);
        // add and store in tmpRes
        AddBinary(res, tmpShift, tmpRes);
        // new res is tmpRes
        for (j = 0; j < DEF_LEN; j++)
            res[j] = tmpRes[j];
    }
}

void DebugOutput(const char* sz, int* a)
{
    int i;

    printf("%s: ", sz);
    for (i = DEF_LEN - 1; i >= 0; i--)
        printf("%d", a[i]);
    printf("\n");
}

void BinaryComplement(int *a, int* res)
{
    int i;

    //save plus one binary number
    int One[DEF_LEN];
    Int64ToBinary(1, One);

    //first complement
    int TmpRes[DEF_LEN];
    for(i = 0; i < DEF_LEN;i++)
        TmpRes[i] = 1-a[i];

    //add first complement and one for second complement
    AddBinary(TmpRes, One, res);
}

int BinaryToInt(int* a){
    int i;
    int result = 0;

    for (i = DEF_LEN-1; i >= 0; i--)
    {
        result <<=1;
        if(a[i])
            result++;
    }
    return result;
}

