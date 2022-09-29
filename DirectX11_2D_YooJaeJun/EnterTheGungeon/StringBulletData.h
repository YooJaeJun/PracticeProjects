#pragma once

namespace Gungeon
{
    class StringBulletData
    {
    public:
        void SetStringBullet();

    public:
        //���ڿ� �Ѿ�
        string  inputString;
        int     outputAlphbets[40][5][5];
        float   coefMidForTarget;

        int A[5][5] = { { 0, 0, 1, 0, 0 }, { 0, 1, 0, 1, 0 }, { 1, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 1 } };
        int B[5][5] = { { 1, 1, 1, 1, 0 }, { 1, 0, 0, 0, 1 }, { 1, 1, 1, 1, 0 }, { 1, 0, 0, 0, 1 }, { 1, 1, 1, 1, 0 } };
        int C[5][5] = { { 0, 1, 1, 1, 1 }, { 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0 }, { 0, 1, 1, 1, 1 } };
        int D[5][5] = { { 1, 1, 1, 1, 0 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 1, 1, 1, 1, 0 } };
        int E[5][5] = { { 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 0 }, { 1, 1, 1, 1, 0 }, { 1, 0, 0, 0, 0 }, { 1, 1, 1, 1, 1 } };
        int F[5][5] = { { 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 0 }, { 1, 1, 1, 1, 0 }, { 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0 } };
        int G[5][5] = { { 0, 1, 1, 1, 1 }, { 1, 0, 0, 0, 0 }, { 1, 0, 0, 1, 1 }, { 1, 0, 0, 0, 1 }, { 0, 1, 1, 1, 1 } };
        int H[5][5] = { { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 } };
        int I[5][5] = { { 0, 1, 1, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 1, 1, 1, 0 } };
        int J[5][5] = { { 0, 0, 1, 1, 1 }, { 0, 0, 0, 1, 0 }, { 0, 0, 0, 1, 0 }, { 1, 0, 0, 1, 0 }, { 1, 1, 1, 1, 0 } };
        int K[5][5] = { { 1, 0, 0, 0, 1 }, { 1, 0, 0, 1, 0 }, { 1, 1, 1, 0, 0 }, { 1, 0, 0, 1, 0 }, { 1, 0, 0, 0, 1 } };
        int L[5][5] = { { 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0 }, { 1, 1, 1, 1, 0 } };
        int M[5][5] = { { 1, 0, 0, 0, 1 }, { 1, 1, 0, 1, 1 }, { 1, 0, 1, 0, 1 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 } };
        int N[5][5] = { { 1, 0, 0, 0, 1 }, { 1, 1, 0, 0, 1 }, { 1, 0, 1, 0, 1 }, { 1, 0, 0, 1, 1 }, { 1, 0, 0, 0, 1 } };
        int O[5][5] = { { 0, 1, 1, 1, 0 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 0, 1, 1, 1, 0 } };
        int P[5][5] = { { 1, 1, 1, 1, 0 }, { 1, 0, 0, 0, 1 }, { 1, 1, 1, 1, 0 }, { 1, 0, 0, 0, 0 }, { 1, 0, 0, 0, 0 } };
        int Q[5][5] = { { 0, 1, 1, 1, 0 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 1, 1 }, { 0, 1, 1, 1, 1 } };
        int R[5][5] = { { 1, 1, 1, 1, 0 }, { 1, 0, 0, 0, 1 }, { 1, 1, 1, 1, 0 }, { 1, 0, 0, 1, 0 }, { 1, 0, 0, 0, 1 } };
        int S[5][5] = { { 0, 1, 1, 1, 1 }, { 1, 0, 0, 0, 0 }, { 0, 1, 1, 1, 0 }, { 0, 0, 0, 0, 1 }, { 1, 1, 1, 1, 0 } };
        int T[5][5] = { { 1, 1, 1, 1, 1 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 } };
        int U[5][5] = { { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 0, 1, 1, 1, 0 } };
        int V[5][5] = { { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 0, 1, 0, 1, 0 }, { 0, 0, 1, 0, 0 } };
        int W[5][5] = { { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 1, 0, 1, 0, 1 }, { 1, 0, 1, 0, 1 }, { 0, 1, 0, 1, 0 } };
        int X[5][5] = { { 1, 0, 0, 0, 1 }, { 0, 1, 0, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 1, 0, 1, 0 }, { 1, 0, 0, 0, 1 } };
        int Y[5][5] = { { 1, 0, 0, 0, 1 }, { 0, 1, 0, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 } };
        int Z[5][5] = { { 1, 1, 1, 1, 1 }, { 0, 0, 0, 1, 0 }, { 0, 0, 1, 0, 0 }, { 0, 1, 0, 0, 0 }, { 1, 1, 1, 1, 1 } };
        int num0[5][5] = { { 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1 } };
        int num1[5][5] = { { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 }, { 0, 0, 1, 0, 0 } };
        int num2[5][5] = { { 1, 1, 1, 1, 1 }, { 0, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 0 }, { 1, 1, 1, 1, 1 } };
        int num3[5][5] = { { 1, 1, 1, 1, 1 }, { 0, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1 }, { 0, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1 } };
        int num4[5][5] = { { 1, 0, 0, 0, 1 }, { 1, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1 }, { 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1 } };
        int num5[5][5] = { { 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 0 }, { 1, 1, 1, 1, 1 }, { 0, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1 } };
        int num6[5][5] = { { 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 0 }, { 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1 } };
        int num7[5][5] = { { 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1 } };
        int num8[5][5] = { { 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1 } };
        int num9[5][5] = { { 1, 1, 1, 1, 1 }, { 1, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1 }, { 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1 } };
        int space[5][5] = { { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0 } };
        // int kik[5][5] = { { 1, 1, 1, 1, 1 }, { 0, 0, 0, 0, 1 }, { 1, 1, 1, 1, 1 }, { 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 1 } };
        // int hih[5][5] = { { 0, 0, 1, 0, 0 }, { 1, 1, 1, 1, 1 }, { 0, 1, 1, 1, 0 }, { 1, 0, 0, 0, 1 }, { 0, 1, 1, 1, 0 } };
    };
}