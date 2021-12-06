#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <math.h>


using namespace std;
void gotoxy(SHORT x, SHORT y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}

int main()
{

    // First we have a circle with radius R1 (we'll take it as 1 here) centered at point(R2,0,0)
    // We can draw the circle by sweeping an angle theta
    // (x,y,z) = (R2,0,0) + (R1cosθ, R1sinθ , 0)
    // Now we take that circle and rotate it by multiplying it with rotation matrix against the y-axis
    // We must also rotate it aganinst two other axis so multiply it by two mroe matrices.

    float A,B;
    A = B = 0;
    float phi, theta;
    // We must have a constant K1, which is our screen distance
    int k1;


    // We have to have our z-buffer
    float z[1760];
    char b[1760];

    // Our theta spacing would be 0.07
    // Our phi spacing would be 0.02

    // A way of clearing the screen and set cursor to home
    cout << "\x1b[2J";
    while (true)
    {
        memset(b,32,1760);
        memset(z,0,7040);
        // 6.28 is 2pi
        for (theta = 0; theta < 6.28; theta+= 0.07)
        {
            for (phi = 0; phi < 6.28; phi += 0.02)
            {
                float c = sin(phi);
                float d = cos(theta);
                float e = sin(A);
                float f = sin(theta);
                float g = cos(A);
                float h  = d+2; // because R2 is taken as 2 double R1
                float D = 1 / (c*h*e+f*g+5); // K2 is taken as 5
                float l = cos(phi);
                float m = cos(B);
                float n = sin(B);
                float t = c*h*g-f*e;

                int x = 40 + 30 * D * (l*h*m-t*n);
                int y = 12+15*D*  (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o])
                {
                    // String D in z-buffer
                    z[o] = D;

                    // Choosing ASCII character based on Luminance and storing it in buffer
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        cout << "\x1b[H";
        for (k1 = 0; k1 < 1761; k1++)
        {
            putchar(k1 % 80 ? b[k1] : 10);
            A += 0.00004;
            B += 0.00002;
        }
        //Sleep(10);
        gotoxy(0,0);
    }
    return 0;
}
