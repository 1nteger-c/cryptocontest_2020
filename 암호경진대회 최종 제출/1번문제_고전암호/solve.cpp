// g++ -o solve solve.cpp
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <time.h>
using namespace std;

#define FLAG_LEN 1285   // 평문의 길이 = 1285
#define KEY_LEN 5   // 키의 길이 = 5 (열마다 계산할 것이므로)

typedef uint8_t UCHAR;

/* 출처 : https://en.wikipedia.org/wiki/Letter_frequency */
double LF[26] = {8.497, 1.492, 2.202, 4.253, 11.162, 2.228, 2.015, 6.094, 7.546, 0.153, 1.292, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 7.587, 6.327, 9.356, 2.758, 0.978, 2.560, 0.150, 1.994, 0.077};

/* 이 함수는 후보키의 IML과 Real IML의 차이가 작은 순으로 후보키들을 배열한다. */
bool comp(pair<UCHAR*, double> a, pair<UCHAR*, double> b){
    return a.second < b.second;
}

/* 이 배열은 후보키들에 대해 전수조사를 할 때 사용한다. */
UCHAR KEY_13[371293][KEY_LEN] = { 0 };  // mod13
UCHAR KEY_26[3200][KEY_LEN] = { 0 };    // mod26

/*
1. 암호문을 데이터에 저장한다.
cipher.txt에는 문제로 받은 암호문이 들어있다. "HRDKHUB..." 
암호문을 c라는 배열에 넣어준다.
*/
UCHAR c[FLAG_LEN] = { 0 };
void read_ciphertext(void){
    FILE *fp = fopen("cipher.txt", "rb");
    for(int i=0;i<FLAG_LEN;i++)
        c[i] = fgetc(fp) - 0x41;
    fclose(fp);
}

/*
2. mod13을 적옹하여 빈도수 분석을 한다.
371293개의 후보키 중 Real IML과 가까운 IML을 가지는 키 100개만 뽑을 것이다.
*/
vector< pair<UCHAR* , double> > z13;
void z13_process(void){
    // 빈도수 또한 mod13을 해준다면, A와 N은 mod113에 대해 같은 값을 가지므로 두 빈도수를 더하여 새로운 배열을 만들어야 한다.
    double LF_13[13] = { 0 };
    for(int i=0;i<13;i++){
        LF_13[i] = LF[i]+LF[i+13];
    }

    // Real IML을 계산한다.
    double real_IML = 0;
    for(int i=0;i<13;i++)
        real_IML += -log(LF_13[i])/log(2)*LF_13[i]/100;
    
    // mod13에 대해 전수조사할 키를 만든다. [0,0,0,0,0]~[12,12,12,12,12]
    for(int i=0;i<pow(13,KEY_LEN);i++){
        int value = i;
        for(int j=0;j<KEY_LEN;j++){
            KEY_13[i][j] = value % 13;
            value = value / 13;
        }
    }

    // |후보키로 복호화한 평문의 IML - Real IML|이 작을 수록 실제 키일 가능성이 높은 것이다.
    for(int i=0;i<pow(13,KEY_LEN);i++){
        double coeff = 0;
        for(int j=0;j<FLAG_LEN/KEY_LEN;j++){
            int sum = 0;
            for(int k=0;k<KEY_LEN;k++){
                sum = (sum+c[KEY_LEN*j+k]*KEY_13[i][k])%13;
            }
            coeff += -log(LF_13[sum])/log(2);
        }
        coeff = coeff / (FLAG_LEN/KEY_LEN);
        coeff = abs(coeff - real_IML);
        z13.push_back(make_pair(KEY_13[i], coeff));
    }

    // 후보키들을 |후보키로 복호화한 평문의 IML - Real IML|가 작은 순으로 정렬한다.
    sort(z13.begin(), z13.end(), comp);
}

/*
3. mod13으로 간추린 후보키 100개에 대해 중국인의 나머지 정리(CRT)를 이용하여 mod26으로 확장하고 빈도수 분석을 한다.
mod2에 대해서는 전수조사를 할 것이다. [0,0,0,0,0]~[1,1,1,1,1]
따라서 우리는 32*100개 키에 대한 전수조사만 수행하면 된다.
*/
vector< pair<UCHAR*, double> > z26;
void z26_process(void){
    // Real IML을 계산한다.
    double real_IML = 0;
    for(int i=0;i<26;i++){
        real_IML += -log(LF[i])/log(2)*LF[i]/100;
    }

    // 중국인의 나머지 정리를 이용하여 키를 생성한다.
    for(int i=0;i<100;i++){
        // key (mod 13)
        int key_13[KEY_LEN] = { 0 };
        for(int j=0;j<KEY_LEN;j++){
            key_13[j] = (z13[i].first)[j];
        }
        for(int j=0;j<pow(2,KEY_LEN);j++){
            // key (mod 2)
            int key_2[KEY_LEN] = { 0 };
            int value = j;
            for(int k=0;k<KEY_LEN;k++){
                key_2[k] = value % 2;
                value = value / 2;
            }
            for(int k=0;k<KEY_LEN;k++){
                // CRT
                KEY_26[32*i+j][k] = (key_2[k]*13+key_13[k]*14)%26;
            }
        }
    }

    // |후보키로 복호화한 평문의 IML - Real IML|이 작을 수록 실제 키일 가능성이 높은 것이다.
    for(int i=0;i<100;i++){
        for(int j=0;j<pow(2,KEY_LEN);j++){
            double coeff = 0;
            for(int k=0;k<FLAG_LEN/KEY_LEN;k++){
                int sum = 0;
                for(int l=0;l<KEY_LEN;l++){
                    sum = (sum+c[KEY_LEN*k+l]*KEY_26[32*i+j][l])%26;
                }
                coeff += -log(LF[sum])/log(2);
            }
            coeff = coeff / (FLAG_LEN/KEY_LEN);
            coeff = abs(coeff - real_IML);
            z26.push_back(make_pair(KEY_26[32*i+j], coeff));
        }
    }
    
    // 후보키들을 |후보키로 복호화한 평문의 IML - Real IML|가 작은 순으로 정렬한다.
    sort(z26.begin(), z26.end(), comp);
}

/*
4. 빈도수 분석을 통해 복호화 키를 구하고 평문을 복호화한다.
*/
void solve(void){
    // 정렬된 z26의 2번째, 3번째, 4번째, 1번째, 0번째 순으로 5x5 복호화키 행렬을 이룸을 알 수 있다.
    UCHAR order[5] = {2, 3, 4, 1, 0};

    // 복호화 키를 구한다.
    UCHAR KEY[KEY_LEN][KEY_LEN] = { 0 };
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            KEY[i][j] = (z26[order[i]].first)[j];
        }
    }
    puts("[*] KEY");
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            printf("%02d ", KEY[j][i]);
        }
        puts("");
    }

    // 복호화 키를 이용하여 평문을 구한다.
    puts("\n[*] PLAINTEXT");
    UCHAR m[FLAG_LEN] = { 0 };
    for(int i=0;i<5;i++){
        for(int j=0;j<FLAG_LEN/KEY_LEN;j++){
            UCHAR sum = 0;
            for(int k=0;k<KEY_LEN;k++)
                sum = (sum+c[5*j+k]*KEY[i][k])%26;
            m[5*j+i] = sum;
        }
    }
    for(int i=0;i<FLAG_LEN;i++){
        printf("%c", m[i]+0x61);
    }
    printf("\n");
}

int main(void){
    clock_t begin = clock();
    read_ciphertext();
    z13_process();
    z26_process();
    solve();
    float t = (float)(clock()-begin) / CLOCKS_PER_SEC;
    puts("\n[*] Elapsed Time");
    printf("%.3fs\n", t);
}