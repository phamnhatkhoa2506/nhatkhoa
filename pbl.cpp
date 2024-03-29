#include <graphics.h>
#include <bits/stdc++.h>
#include "Dohoa.h"
using namespace std;

int d = 1;
#define E 2.718281828;
#define Pi M_PI;

void decorate_console();
void draw_calculator();
void num_and_operator();
void draw_suffix_table();
string input(int &mode, int xo, int yo);
void out_screen(vector<int> &v, string &s, int tungdo, string temp, int &yo);
void erase_screen(string &s, int x, int y, int times); 
int isdigit(char c);
int isoperatorc(char c);
int isoperator(string c);
int pri(string c);
int isspecial(string s);
int is_sin(string s);
double equalspecial(string s, double tmp);
int is_alpha(string s);
double equal(queue<string> q, int mode);
string tinh_value_x(string s, int mode);
string read_special_func(string temp, string &sign_operator);
void solve(string s, string value_x, int mode);

main(){
	// Khởi tạo đồ hoạ///////////////////////////////////
	initwindow(1500, 1000); setbkcolor(WHITE); cleardevice(); settextstyle(1, 0, 4); setcolor(BLACK); setrgbpalette(1, 23, 45, 40);
	decorate_console(); draw_calculator(); num_and_operator(); draw_suffix_table();
	// Cái chính ////////////////////////////////////////
	int mode = 1; setcolor(BLACK);
	ifstream input_file; input_file.open("file_input.txt");
	while(1){
		string c = input(mode, 270, 100); 
		setbkcolor(WHITE); settextstyle(1, 0, 3);	
		if (c == "read from file" or c == "Input from console"){
			cout << "Bieu thuc " << d++ << " : ";
			string g;
			if (c == "read from file"){
				setfillstyle(SOLID_FILL, WHITE); bar(260, 90, 740, 285); rectangle(260, 90, 740, 285); bar(800, 85, 1200, 300); rectangle(800, 85, 1200, 300);
				if (input_file.peek() == EOF) {input_file.close(); input_file.open("file_input.txt");}
				getline(input_file, g); cout << g << endl;
			}
			else getline(cin, g);
		
		    int y = 100; moveto(270, 100);
		    char temp[2]; temp[1] = '\0';
		    for (int i = 0; i < g.length(); i++){
				if (g[i] == ' ') continue; temp[0] = g[i];
		      	if (getx() >= 720) {y += 25; moveto(270, y);} outtext(temp);
		    }
				
			string value_x;
	        for(string::iterator it = g.begin(); it != g.end(); it++){
		        if(*it == 'x'){
		            cout << "Nhap gia tri cua bien x : "; getline(cin, value_x);
		            outtextxy(270, 230, "x = "); moveto(330, 230);
				    for (int i = 0; i < value_x.length(); i++){
				      	if (value_x[i] == ' ') continue; temp[0] = value_x[i];
				      	outtext(temp);
				    } break;
		        }
	        }
	        if (c == "Input from console" ){cout << "Chon che do: " << endl << "1. Radian" << endl << "2. Degree" << endl << "Chon: "; cin >> mode;}
	        solve(g, value_x, mode);
		}
		else {
	        cout << "Bieu thuc " << d++ << " : " << c << endl;
	      	string value_x; bool check = false;
	        for(string::iterator it = c.begin(); it != c.end(); it++){
	            if(*it == 'x'){
	                cout << "Nhap gia tri cua bien x : "; outtextxy(270, 230, "x = ");
					value_x = input(mode, 330, 230); cout << value_x << endl;
					check = !check; break;
	            }
	        }
	        if (value_x == "" and check) { cout << endl; continue;}
	        solve(c, value_x, mode);
		}
	}
	input_file.close(); getch(); closegraph();
}
void decorate_console(){
	mau(3);	phongto(15, 19); cmd(1400, 1000); cout << endl;
	for (int i = 0; i < 37; i++) cout << ' '; cout << "PBL1" << endl;
	for (int i = 0; i < 12; i++) cout << ' '; cout << "Covert expression to suffix expression and calculate result" << endl; 
	for (int i = 0; i < 26; i++) cout << ' '; cout << "Members : " << "Huynh Canh Vien" << endl;
	for (int i = 0; i < 36; i++) cout << ' '; cout << "Pham Nhat Khoa" << endl;
	for (int i = 0; i < 82; i++) cout << '-'; cout << endl;
	mau(14); phongto(13, 16);
}
void erase_screen(string &s, int x, int y, int times){
	bar(getx(), gety(), getx() - x, gety() + y); moveto(getx() - x, gety());
	for (int i = 0; i < times; i++) s.pop_back();
}
void out_screen(vector<int> &v, string &s, int tungdo, string temp, int &yo) {
	if (getx() >= tungdo) {v.push_back(getx()); yo += 25; moveto(270, yo);} 
	s += temp; char tmp[temp.length() + 1]; tmp[temp.length()] = '\0';
	for (int i = 0; i < temp.length(); i++) tmp[i] = temp[i]; outtext(tmp);
}
string input(int &mode, int xo, int yo) {	
	string s; vector<int> hoanhdo;
	int yoo = yo, x, y; moveto(xo, yo);
	while (1){
	    delay(0.0001);
	    if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			// hàng 1
			{
				if (x >= 260 and x <= 360 and y >= 300 and y <= 360) out_screen(hoanhdo, s, 720, "+", yo); // + 
				if (x >= 387 and x <= 487 and y >= 300 and y <= 360) out_screen(hoanhdo, s, 720, "-", yo); // -
				if (x >= 514 and x <= 614 and y >= 300 and y <= 360) out_screen(hoanhdo, s, 720, "*", yo); // *
				if (x >= 641 and x <= 741 and y >= 300 and y <= 360) out_screen(hoanhdo, s, 720, "/", yo); // /
			}
			// hàng 2
			{
				if (x >= 260 and x <= 360 and y >= 370 and y <= 430) out_screen(hoanhdo, s, 720, "7", yo); // 7
				if (x >= 387 and x <= 487 and y >= 370 and y <= 430) out_screen(hoanhdo, s, 720, "8", yo); // 8
				if (x >= 514 and x <= 614 and y >= 370 and y <= 430) out_screen(hoanhdo, s, 720, "9", yo); // 9
				if (x >= 641 and x <= 741 and y >= 370 and y <= 430) out_screen(hoanhdo, s, 720, "^", yo); // ^
			}
			// hàng 3
			{
				if (x >= 260 and x <= 360 and y >= 440 and y <= 500) out_screen(hoanhdo, s, 720, "4", yo); // 4
				if (x >= 387 and x <= 487 and y >= 440 and y <= 500) out_screen(hoanhdo, s, 720, "5", yo); // 5
				if (x >= 514 and x <= 614 and y >= 440 and y <= 500) out_screen(hoanhdo, s, 720, "6", yo); // 6
				if (x >= 641 and x <= 741 and y >= 440 and y <= 500) out_screen(hoanhdo, s, 720, "%", yo); // %
			}
			// hàng 4
			{
				if (x >= 260 and x <= 360 and y >= 510 and y <= 570) out_screen(hoanhdo, s, 720, "1", yo); // 1
				if (x >= 387 and x <= 487 and y >= 510 and y <= 570) out_screen(hoanhdo, s, 720, "2", yo); // 2
				if (x >= 514 and x <= 614 and y >= 510 and y <= 570) out_screen(hoanhdo, s, 720, "3", yo); // 3
				// AC
				if (x >= 641 and x <= 741 and y >= 510 and y <= 570)  {
					setfillstyle(SOLID_FILL, WHITE);
					bar(260, 90, 740, 285);
					rectangle(260, 90, 740, 285);
					bar(800, 85, 1200, 300);
					rectangle(800, 85, 1200, 300);
					yo = 100;
					moveto(270, 100); 
					s = "";
					if (yo >= 230) return s;
				} 
			}
			// hàng 5
			{
				if (x >= 260 and x <= 360 and y >= 580 and y <= 640) out_screen(hoanhdo, s, 720, "0", yo); // 0
				if (x >= 387 and x <= 487 and y >= 580 and y <= 640) out_screen(hoanhdo, s, 720, ".", yo); // .
				if (x >= 514 and x <= 614 and y >= 580 and y <= 640) out_screen(hoanhdo, s, 720, "x", yo); // X
				if (x >= 641 and x <= 741 and y >= 580 and y <= 640) return s; // =
	    	}
			// hàm đặc biệt
			{
				{
					if (x >= 40 and x <= 150 and y >= 300 and y <= 360) {return "";} // Nút ON
					if (x >= 40 and x <= 150 and y >= 370 and y <= 430) {closegraph(); exit(1);} // Nút OFF
					if (x >= 800 and x <= 880 and y >= 330 and y <= 380) out_screen(hoanhdo, s, 720, "e", yo); 	// e
					if (x >= 800 and x <= 880 and y >= 390 and y <= 440) out_screen(hoanhdo, s, 680, "sin", yo); // sin
					if (x >= 800 and x <= 880 and y >= 450 and y <= 500) out_screen(hoanhdo, s, 670, "asin", yo); // asin	
					if (x >= 800 and x <= 880 and y >= 510 and y <= 560) out_screen(hoanhdo, s, 700, "ln", yo); // ln	
					if (x >= 800 and x <= 880 and y >= 570 and y <= 620) out_screen(hoanhdo, s, 700, "rt", yo); // rt
					if (x >= 906 and x <= 986 and y >= 330 and y <= 380) out_screen(hoanhdo, s, 700, "pi", yo);	// pi	
					if (x >= 906 and x <= 986 and y >= 390 and y <= 440) out_screen(hoanhdo, s, 680, "cos", yo); // cos
					if (x >= 906 and x <= 986 and y >= 450 and y <= 500) out_screen(hoanhdo, s, 670, "acos", yo); // acos		
					if (x >= 906 and x <= 986 and y >= 510 and y <= 560) out_screen(hoanhdo, s, 680, "log", yo); // log			
					if (x >= 906 and x <= 986 and y >= 570 and y <= 620) out_screen(hoanhdo, s, 680, "abs", yo); // abs		
					if (x >= 1012 and x <= 1092 and y >= 330 and y <= 380) out_screen(hoanhdo, s, 720, "(", yo); // (		
					if (x >= 1012 and x <= 1092 and y >= 390 and y <= 440) out_screen(hoanhdo, s, 680, "tan", yo); // tan		
					if (x >= 1012 and x <= 1092 and y >= 450 and y <= 500) out_screen(hoanhdo, s, 670, "atan", yo); // atan		
					if (x >= 1012 and x <= 1092 and y >= 510 and y <= 560) out_screen(hoanhdo, s, 670, "sqrt", yo); // sqrt		
					if (x >= 1012 and x <= 1092 and y >= 570 and y <= 620) out_screen(hoanhdo, s, 720, "%", yo); // %	
					if (x >= 1118 and x <= 1198 and y >= 330 and y <= 380) out_screen(hoanhdo, s, 720, ")", yo); // )
					if (x >= 1118 and x <= 1198 and y >= 390 and y <= 440) out_screen(hoanhdo, s, 680, "cot", yo); // cot
					if (x >= 1118 and x <= 1198 and y >= 450 and y <= 500) out_screen(hoanhdo, s, 670, "acot", yo); // acot
					if (x >= 1118 and x <= 1198 and y >= 510 and y <= 560) out_screen(hoanhdo, s, 670, "cbrt", yo); // cbrt
					if (x >= 1118 and x <= 1198 and y >= 570 and y <= 620) out_screen(hoanhdo, s, 680, "mod", yo); // mod
					// Nút degree <-> radian
					if (x >= 40 and x <= 150 and y <= 140 and y >= 90){
		            	setrgbpalette(8, 255, 204, 78); setfillstyle(SOLID_FILL, 8);
						bar(40, 90, 150, 140); rectangle(40, 90, 150, 140);
						settextstyle(3, 0, 4); setbkcolor(8);
				        if (mode == 1){ mode = 2; outtextxy(44, 97, "Degree");}
				        else if (mode == 2){ mode = 1; outtextxy(44, 97, "Radian");}
						settextstyle(1, 0, 2); setbkcolor(WHITE);
			    	}	    	
			    	if (x >= 30 and y >= 500 and x <= 190 and y <= 560) return "read from file"; // Nút read from file 
			    	if (x >= 30 and y >= 580 and x <= 190 and y <= 640) return "Input from console"; 	// Nút input from console
		    	}
		    	// Nút Delete
				if (x >= 40 and y >= 160 and x <= 150  and y <= 210)
		    	{
		    		setfillstyle(SOLID_FILL, WHITE);
		    		if (!s.empty())
		    		{
		    			if (s[s.length() - 1] == '+') erase_screen(s, 23, 20, 1);
						else if (s[s.length() - 1] == '-') erase_screen(s, 13, 20, 1);
						else if (s[s.length() - 1] == '*') erase_screen(s, 20, 20, 1);
						else if (s[s.length() - 1] == '/') erase_screen(s, 11, 22, 1);
						else if (s[s.length() - 1] == '^') erase_screen(s, 19, 20, 1);
						else if (s[s.length() - 1] == '.') erase_screen(s, 10, 20, 1);
						else if (s[s.length() - 1] == 'x') erase_screen(s, 20, 20, 1);
						else if (s[s.length() - 1] == 'e') erase_screen(s, 18, 20, 1);
						else if (s[s.length() - 1] == '(') erase_screen(s, 13, 25, 1);
						else if (s[s.length() - 1] == ')') erase_screen(s, 13, 25, 1);
						else if (s[s.length() - 1] == '%') erase_screen(s, 33, 20, 1);
						else if (s[s.length() - 1] == 'i' and s[s.length() - 2] == 'p') erase_screen(s, 31, 25, 2);
						else if (s[s.length() - 1] == 't' and s[s.length() - 2] == 'r' and s[s.length() - 3] == 'q' and s[s.length() - 4] == 's') erase_screen(s, 60, 25, 4);
						else if (s[s.length() - 1] == 't' and s[s.length() - 2] == 'r' and s[s.length() - 3] == 'b' and s[s.length() - 4] == 'c') erase_screen(s, 62, 20, 4);
						else if (s[s.length() - 1] == 't' and s[s.length() - 2] == 'r') erase_screen(s, 24, 20, 2);
						else if (s[s.length() - 1] == 'n' and s[s.length() - 2] == 'l') erase_screen(s, 31, 20, 2);
		    			else if (s[s.length() - 1] == 'g' and s[s.length() - 2] == 'o' and s[s.length() - 3] == 'l') erase_screen(s, 51, 25, 3);
						else if (s[s.length() - 1] == 's' and s[s.length() - 2] == 'b' and s[s.length() - 3] == 'a') erase_screen(s, 54, 25, 3);
						else if (s[s.length() - 1] == 'n' and s[s.length() - 2] == 'i' and s[s.length() - 3] == 's' and s[s.length() - 4] == 'a') erase_screen(s, 65, 20, 4);
						else if (s[s.length() - 1] == 's' and s[s.length() - 2] == 'o' and s[s.length() - 3] == 'c' and s[s.length() - 4] == 'a') erase_screen(s, 72, 20, 4);
						else if (s[s.length() - 1] == 'n' and s[s.length() - 2] == 'a' and s[s.length() - 3] == 't' and s[s.length() - 4] == 'a') erase_screen(s, 67, 20, 4);
		    			else if (s[s.length() - 1] == 't' and s[s.length() - 2] == 'o' and s[s.length() - 3] == 'c' and s[s.length() - 4] == 'a') erase_screen(s, 67, 20, 4);
		    			else if (s[s.length() - 1] == 'n' and s[s.length() - 2] == 'i' and s[s.length() - 3] == 's') erase_screen(s, 47, 20, 3);
		    			else if (s[s.length() - 1] == 's' and s[s.length() - 2] == 'o' and s[s.length() - 3] == 'c') erase_screen(s, 54, 20, 3);
		    			else if (s[s.length() - 1] == 'n' and s[s.length() - 2] == 'a' and s[s.length() - 3] == 't') erase_screen(s, 49, 20, 3);
		    			else if (s[s.length() - 1] == 't' and s[s.length() - 2] == 'o' and s[s.length() - 3] == 'c') erase_screen(s, 49, 20, 3);
		    			else if (s[s.length() - 1] == 'd' and s[s.length() - 2] == 'o' and s[s.length() - 3] == 'm') erase_screen(s, 71, 20, 3);
		    			else if (isalnum(s[s.length() - 1])) erase_screen(s, 20, 20, 1);
		    		
		    			if (s.empty()) moveto(xo, yo);
		    			else if (getx() <= 270)
						{
							if (!hoanhdo.empty())
							{
								yo -= 25;
							  	moveto(hoanhdo[hoanhdo.size() - 1], yo);
							  	hoanhdo.pop_back();
							}
							else moveto(xo, yoo);
						}
					}
				}
			}
		}
	}
}
void num_and_operator() {
	// Dau +
	for (int i = 280; i <= 340; i++){
		if (i < 300 or i > 320)	for (int j = 323; j <= 337; j++) putpixel(i, j, WHITE);
		else for (int j = 310; j <= 350; j++) putpixel(i, j, WHITE);
	}
 	// Dau -
 	for (int i = 410; i <= 465; i++) 
	 	for (int j = 323; j <= 337; j++) putpixel(i, j, WHITE);
	// Dau x
	setbkcolor(BLACK); setcolor(WHITE); settextstyle(1, 0, 5); outtextxy(548, 313, "*");
	// Dau /
	setfillstyle(SOLID_FILL, WHITE); fillellipse(692, 315, 7, 7); fillellipse(692, 346, 7, 7);
	for (int i = 662; i <= 722; i++) 
		for (int j = 325; j <= 336; j++) putpixel(i, j, WHITE);
	// Dấu ^
	setbkcolor(RED); setcolor(YELLOW); settextstyle(1, 0, 5); outtextxy(675, 380, "^");
	// Dấu %
	outtextxy(662, 448, "%");
	// In số
	settextstyle(4, 0, 5); setbkcolor(WHITE); setcolor(BLACK);
	outtextxy(290, 377, "7"); outtextxy(290, 447, "4"); outtextxy(290, 517, "1"); outtextxy(290, 587, "0");
	outtextxy(420, 377, "8"); outtextxy(420, 447, "5"); outtextxy(420, 517, "2");
	outtextxy(545, 377, "9"); outtextxy(545, 447, "6"); outtextxy(545, 517, "3");
	// Dấu .
	fillellipse(437, 617, 7, 7);
	// Biến x
	setbkcolor(BROWN); setcolor(WHITE); outtextxy(544, 588, "X");
	// Dấu =
	for (int i = 662; i <= 722; i++) {
		for (int j = 590; j <= 605; j++) putpixel(i, j, RED);
		for (int j = 615; j <= 630; j++) putpixel(i, j, RED);
	}
	// Chữ AC, ON, OFF
	settextstyle(4, 0, 5); setbkcolor(RED); setcolor(YELLOW); outtextxy(647, 520, "AC");
	// Vẽ các hàm đặc biệt
	setfillstyle(SOLID_FILL, 8); setcolor(BLACK); settextstyle(4, 0, 4);
	for (int i = 0; i < 5; i++){
		int x = 800, y = 330 + i * 60;
		if (i == 0) setrgbpalette(8, 230, 147, 94);
		else if (i == 1) setrgbpalette(8, 37, 205, 255);
		else if (i == 2) setrgbpalette(8, 255, 240, 100);
		else if (i == 3) setrgbpalette(8, 24, 255, 73);
		else if (i == 4) setrgbpalette(8, 235, 196, 235);
		for (int j = 0; j < 4; j++){ bar(x, y, x + 80, y + 50); rectangle(x, y, x + 80, y + 50); x += 106; }
	}
	setrgbpalette(8, 230, 147, 94); setbkcolor(8);
	outtextxy(826, 337, "e"); outtextxy(928, 337, "pi"); outtextxy(1042, 337, "("); outtextxy(1148, 337, ")");
	setrgbpalette(8, 37, 205, 255);
	outtextxy(809, 396, "sin"); outtextxy(908, 396, "cos"); outtextxy(1019, 397, "tan"); outtextxy(1124, 397, "cot");
	line(986, 390, 986, 440);
	setrgbpalette(8, 24, 255, 73);
	outtextxy(824, 517, "ln"); outtextxy(913, 517, "log");
	settextstyle(4, 0, 3);
	outtextxy(1022, 522, "sqrt"); outtextxy(1127, 522, "cbrt");
	setrgbpalette(8, 255, 240, 100);
	outtextxy(808, 462, "asin"); outtextxy(908, 462, "acos"); outtextxy(1017, 462, "atan"); outtextxy(1123, 462, "acot");
	setrgbpalette(8, 235, 196, 235);
	outtextxy(918, 582, "abs");
	settextstyle(4, 0, 4);
	outtextxy(824, 576, "rt"); outtextxy(1030, 580, "%");
	settextstyle(4, 0, 3);
	outtextxy(1124, 582, "mod");
	// ON OFF
	settextstyle(4, 0, 5); setcolor(BLACK);
	rectangle(40, 300, 150, 360); bar(40, 300, 150, 360);
	rectangle(40, 370, 150, 430); bar(40, 370, 150, 430);
	setbkcolor(8); setcolor(RED); outtextxy(45, 308, "ON");
	settextstyle(4, 0, 4); outtextxy(45, 385, "OFF");
	// Read from file
	setrgbpalette(8, 37, 205, 255); setbkcolor(8); settextstyle(4, 0, 2);
	rectangle(30, 500, 190, 560); bar(30, 500, 190, 560);
	outtextxy(35, 510, "Read from"); outtextxy(90, 530, "file");
	// Input from console
	rectangle(30, 580, 190, 640); bar(30, 580, 190, 640);
	outtextxy(37, 590, "Input from"); outtextxy(57, 610, "console");
}
void draw_calculator() {
	// Viền ngoài
	setfillstyle(SOLID_FILL, BLACK); bar(240, 15, 760, 670); rectangle(240, 15, 760, 670);
	// Viền trong
	setfillstyle(SOLID_FILL, LIGHTGRAY); bar(250, 25, 750, 660); rectangle(250, 25, 750, 660);
	// Màn hình
	setfillstyle(SOLID_FILL, WHITE); bar(260, 90, 740, 285); rectangle(260, 90, 740, 285);
	setbkcolor(LIGHTGRAY); outtextxy(420, 40, "CASIO"); 
	setbkcolor(WHITE);
	for (int i = 0; i < 5; i++)
	{
		int x = 260, y = 300 + i*70;;
		for (int j = 0; j < 4; j++) {
			if (i == 0) setfillstyle(SOLID_FILL, BLACK);
			else if (i == 4 and j == 3) setfillstyle(SOLID_FILL, YELLOW);
			else if (i > 0 and j == 3) 	setfillstyle(SOLID_FILL, RED);
			else if ((i < 4 and i > 0 and j < 3) or (i == 4 and j == 0)) setfillstyle(SOLID_FILL, WHITE);
			else setfillstyle(SOLID_FILL, BROWN);	
			bar(x, y, x + 100, y + 60); rectangle(x, y, x + 100, y + 60); x += 127;
		}
	}
	// Ô radian và degree
	setrgbpalette(8, 255, 204, 78); setfillstyle(SOLID_FILL, 8); settextstyle(3, 0, 4); setbkcolor(8);
	bar(40, 90, 150, 140); rectangle(40, 90, 150, 140); outtextxy(44, 97, "Radian");
	// Ô Delete
	setrgbpalette(8, 99, 232, 201); settextstyle(3, 0, 4); setbkcolor(8);
	bar(40, 160, 150, 210); rectangle(40, 160, 150, 210); outtextxy(49, 168, "Delete");
}
void draw_suffix_table(){
	setrgbpalette(8, 221, 245, 88); settextstyle(1, 0, 3); setbkcolor(8); setfillstyle(SOLID_FILL, 8); setcolor(GREEN);
	bar(800, 45, 1200, 85); rectangle(800, 45, 1200, 85); rectangle(800, 85, 1200, 300); outtextxy(860, 52, "Suffix Expression"); 
	setbkcolor(WHITE);
}
int isdigit(char c){return (c >= '0' && c <= '9');}
int isoperatorc(char c){ return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' or c == '%';}
int isoperator(string c){ return c == "+" || c == "-" || c == "*" || c == "/" || c == "^" || c == "mod" or c == "%";}
int pri(string c){
    if(c == "+" || c == "-") return 1;
    if(c == "*" || c == "/" || c == "mod") return 2;
    if(c == "^") return 3;
    if(c == "ln" || c == "log" || c == "sin" || c == "cos" || c == "tan" || c == "cot" || c == "sqrt" || c == "cbrt" || c == "rt") return 4;
    if(c == "ln-" || c == "log-" || c == "sin-" || c == "cos-" || c == "tan-" || c == "cot-" || c == "sqrt-" || c == "cbrt-" || c == "rt-") return 4;
    if(c == "%") return 4;
    if(c == "+()" || c == "-()") return 5;
    return 0;
}
int isspecial(string s){
    if(s == "ln" || s == "cos" || s == "sin" || s == "tan" || s == "cot" || s == "log" ||s == "cbrt" || s == "sqrt" || s == "rt" || s == "abs" || s == "+()" || s == "-()") return 1;
    if(s == "atan" || s == "asin" || s == "acos" || s == "acot" || s == "atan-" || s == "asin-" || s == "acos-" || s == "acot-") return 1;
    if(s == "ln-" || s == "cos-" || s == "sin-" || s == "tan-" || s == "cot-" || s == "log-" || s == "cbrt-" || s == "sqrt-" || s == "rt-" || s == "abs-") return 1;
	return s == "%";
}
int is_sin(string s){ return s == "cos" or s == "sin" or s == "tan" or s == "cot" or s == "cos-" or s == "sin-" or s == "tan-" or s == "cot-";}
int is_asin(string s){return s == "asin" or s == "acos" or s == "atan" or s == "acot" or s == "asin-" or s == "acos-" or s == "atan-" or s == "acot-";}
double equalspecial(string s, double tmp){
    if(s == "ln") return log(tmp);
    if(s == "log") return log(tmp) / log(10);
    if(s == "cos") return cos(tmp);
    if(s == "sin") return sin(tmp);
    if(s == "tan") return tan(tmp);
    if(s == "cot") return 1 / tan(tmp);
    if(s == "sqrt") return sqrt(tmp);
    if(s == "cbrt") return cbrt(tmp);
    if(s == "abs") return fabs(tmp);
    if(s == "+()") return tmp;
    if(s == "atan") return atan(tmp);
    if(s == "asin") return asin(tmp);
    if(s == "acos") return acos(tmp);
    if(s == "acot") return atan(1 / tmp);
    if(s == "-()") return -tmp;
    if(s == "ln-") return -log(tmp);
    if(s == "log-") return -log(tmp) / log(10);
    if(s == "cos-") return -cos(tmp);
    if(s == "sin-") return -sin(tmp);
    if(s == "tan-") return -tan(tmp);
    if(s == "cot-") return -1 / tan(tmp);
    if(s == "sqrt-") return -sqrt(tmp);
    if(s == "cbrt-") return -cbrt(tmp);
    if(s == "abs-") return -fabs(tmp);
    if(s == "atan-") return -atan(tmp);
    if(s == "asin-") return -asin(tmp);
    if(s == "acot-") return -atan(1/tmp);
    if(s == "acos-") return -acos(tmp);
    if(s == "%") return tmp / 100;
    return 0;
}
int is_alpha(string s){return s == "e" || s == "pi" || s == "e-" || s == "pi-";}
double equal(queue<string> q, int mode){
    stack<double> st;
    while(!q.empty()){
        while(!isoperator(q.front()) && !isspecial(q.front()) && !q.empty()){
            if(is_alpha(q.front())){
                if(q.front() == "e") st.push(exp(1));
                else if(q.front() == "e-") st.push(-exp(1));
                else if(q.front() == "pi-") st.push(-M_PI);
                else if(q.front() == "pi") st.push(M_PI);
                q.pop();
            }
            else {st.push(stod(q.front())); q.pop(); }
        }
        if(q.empty()) break;
        if(isspecial(q.front())){
            if(q.front() == "log-" or q.front() == "log"){
                double s = st.top(); st.pop();
                if (q.front() == "log-") st.top() = -log(s) / log(st.top()); else st.top() = log(s) / log(st.top());                
                q.pop();
            }
            else if(q.front() == "rt" or q.front() == "rt-"){
                double s = st.top(); st.pop();
                int dau = 0;
                if(s < 0){ s = -s; dau = 1;}
                if (q.front() == "rt") st.top() = pow(s, 1 / st.top()); else st.top() = -pow(s, 1 / st.top());
                if(dau == 1) st.top() = -st.top();
                q.pop();
            }
            else if (q.front() == "%") {st.top() /= 100; q.pop();}
            else{       
                if(is_sin(q.front()) && mode == 2) st.top() = st.top() * M_PI / 180;
                st.top() = equalspecial(q.front(), st.top());
        		if (mode == 2 and is_asin(q.front())) st.top() = st.top() * 180 / M_PI;
                q.pop();
            }
        }
        else{
            double s = st.top();
            st.pop();
            if(q.front() == "+") st.top() += s;
            else if(q.front() == "-") st.top() -= s;
            else if(q.front() == "*") st.top() *= s;
            else if(q.front() == "/") st.top() /= s;
            else if(q.front() == "^") st.top() = pow(st.top(), s);
            else if(q.front() == "mod") st.top() -= int(st.top() / s) * s;
            q.pop();
        }
    }
    return st.top();
}
string tinh_value_x(string s, int mode){
    queue<string> q; stack<string> st;
    string tmp, sign = "", sign_operator = "";
    for (string::iterator it = s.begin(); it != s.end(); ++it) {
        tmp = ""; tmp += *it;
        if (tmp == " ") continue;
		else if (*it == 'm' and *(it + 1) == 'o' and *(it + 2) == 'd') {tmp = "mod"; goto operator_;}
        else if (isdigit(*it)){
            tmp = ""; tmp += sign; tmp += *it;
            while ((it + 1) != s.end() && (isdigit(*(it + 1)) || *(it + 1) == '.')) { ++it; tmp += *it;}
            q.push(tmp);
            sign = "";
        }
        else if (isoperator(tmp)) {
        	operator_ :
            if (pri(tmp) == 1) { // operator '+' or '-'
                string::iterator jt = it - 1;
                while(*jt == ' ') jt--;
                if(!isdigit(*jt) && !(*jt <= 'z' && *jt >= 'a') && *jt != ')'){
                    int dem = 0;
                    while (*it == '+' || *it == '-' || *it == ' ') {if (*it == '-') dem++; it++;}
                    if (dem % 2 == 0) sign = sign;
                    else { if (sign == "+" || sign == "") sign = "-"; else sign = "";}
                    if(*it >= 'a' && *it <= 'z'){ sign_operator = sign; sign = "";} 
                    else if(*it == '('){ if(sign == "") st.push("+()"); else if(sign == "-") st.push("-()"); sign = "";}
                    it--;
                    continue;
                } 
                else{
                    int count = 0;
                    while(*it == ' ' || isoperatorc(*it)){ if(*it == '-') count++; it++;}
                    if(count % 2 == 0) tmp = "+"; else tmp = "-"; it--;
                    goto start;
                }
            } 
            else {
                start:
                if (st.empty() || st.top() == "(") {st.push(tmp); continue;}
				else if (pri(tmp) > pri(st.top())) st.push(tmp);
                else {q.push(st.top()); st.pop(); goto start;}
            }
        }
        else if (*it == '(') st.push(tmp);
        else if (*it == ')') {
            while (!st.empty() && st.top() != "(") {q.push(st.top()); st.pop();}
            if(!st.empty()) st.pop();
            if(st.top() == "abs" && !st.empty()){ q.push(st.top()); st.pop();}
        }
        else if (*it == 'l' && *(it + 1) == 'n') {++it; st.push(read_special_func("ln", sign_operator));}
        else if (*it == 'l' && *(it + 1) == 'o' && *(it + 2) == 'g') {it += 2; st.push(read_special_func("log", sign_operator));}
        else if (*it == 'c' && *(it + 1) == 'o' && *(it + 2) == 's') {it += 2; st.push(read_special_func("cos", sign_operator));}
        else if (*it == 's' && *(it + 1) == 'i' && *(it + 2) == 'n') {it += 2; st.push(read_special_func("sin", sign_operator));}
        else if (*it == 't' && *(it + 1) == 'a' && *(it + 2) == 'n') {it += 2; st.push(read_special_func("tan", sign_operator));}
        else if (*it == 'c' && *(it + 1) == 'o' && *(it + 2) == 't') {it += 2; st.push(read_special_func("cot", sign_operator));}
        else if (*it == 's' && *(it + 1) == 'q' && *(it + 2) == 'r' && *(it + 3) == 't') {it += 3; st.push(read_special_func("sqrt", sign_operator));}
        else if (*it == 'c' && *(it + 1) == 'b' && *(it + 2) == 'r' && *(it + 3) == 't') {it += 3; st.push(read_special_func("cbrt", sign_operator));}
        else if (*it == 'r' && *(it + 1) == 't') {++it; st.push(read_special_func("rt", sign_operator));}
        else if (*it == 'a' && *(it + 1) == 'b' && *(it + 2) == 's') {it += 2; st.push(read_special_func("abs", sign_operator));}
        else if (*it == 'p' && *(it + 1) == 'i') {++it; q.push(read_special_func("pi", sign_operator));}
        else if (*it == 'e') {q.push(read_special_func("e", sign_operator));}
        else if (*it == 'a' && *(it + 1) == 't' && *(it + 2) == 'a' && *(it + 3) == 'n') {it += 3; st.push(read_special_func("atan", sign_operator));}
        else if (*it == 'a' && *(it + 1) == 's' && *(it + 2) == 'i' && *(it + 3) == 'n') {it += 3; st.push(read_special_func("asin", sign_operator));}
        else if (*it == 'a' && *(it + 1) == 'c' && *(it + 2) == 'o' && *(it + 3) == 's') {it += 3; st.push(read_special_func("acos", sign_operator));}
        else if (*it == 'a' && *(it + 1) == 'c' && *(it + 2) == 'o' && *(it + 3) == 't') {it += 3; st.push(read_special_func("acot", sign_operator));}
    }
    while (!st.empty()) {q.push(st.top()); st.pop();}
    
    double res = equal(q, mode);
    string value_x = to_string(res);
    if (int(res) == res) {for (int i = 0; i < 7; i++) value_x.pop_back();}
 	else {while (value_x[value_x.length() - 1] == '0') value_x.pop_back();}
 	
    return value_x;
}
string read_special_func(string temp, string &sign_operator){temp += sign_operator; sign_operator = ""; return temp;}
void solve(string s, string value_x, int mode) {
    queue<string> q; stack<string> st;
    string tmp, sign = "", sign_operator = "";
    for (string::iterator it = s.begin(); it != s.end(); ++it) {
        tmp = ""; tmp += *it;
        if (tmp == " ") continue;
		else if (*it == 'm' and *(it + 1) == 'o' and *(it + 2) == 'd') {tmp = "mod"; goto operator_;}
        else if (isdigit(*it)){
            tmp = ""; tmp += sign; tmp += *it;
            while ((it + 1) != s.end() && (isdigit(*(it + 1)) || *(it + 1) == '.')) {++it; tmp += *it;}
            q.push(tmp);
            sign = "";
        }
        else if(*it == 'x') q.push(tinh_value_x(value_x, mode));
        else if (isoperator(tmp)) {
        	operator_ :
            if (pri(tmp) == 1) { // operator '+' or '-'
                string::iterator jt = it - 1;
                while(*jt == ' ') jt--;
                if(!isdigit(*jt) && !(*jt <= 'z' && *jt >= 'a') && *jt != ')' && *jt != '%'){
                    int dem = 0;
                    while (*it == '+' || *it == '-' || *it == ' ') {if (*it == '-') dem++; it++;}
                    if (dem % 2 != 0) {if (sign == "+" || sign == "") sign = "-"; else sign = "";}
                    if(*it >= 'a' && *it <= 'z') {sign_operator = sign;sign = "";}
                    else if(*it == '(') {if(sign == "") st.push("+()"); else if(sign == "-") st.push("-()");sign = "";}
                    it--;
                    continue;
                } 
                else{
                    int count = 0;
                    while(*it == ' ' || isoperatorc(*it)) {if(*it == '-') count++; it++;}
                    if(count % 2 == 0) tmp = "+"; else tmp = "-"; it--;
				 	goto start;
                }
            } 
            else {
                start:
                if (st.empty() || st.top() == "(") {st.push(tmp); continue;} 
				else if (pri(tmp) > pri(st.top())) st.push(tmp);
                else {q.push(st.top()); st.pop(); goto start;}
            }
        }
        else if (*it == '(') st.push(tmp);
        else if (*it == ')') {
            while (!st.empty() && st.top() != "(") {q.push(st.top()); st.pop();}
            if(!st.empty()) st.pop();
            if(st.top() == "abs" && !st.empty()) {q.push(st.top()); st.pop();}
        }
	    else if (*it == 'l' && *(it + 1) == 'n') {++it; st.push(read_special_func("ln", sign_operator));}
        else if (*it == 'l' && *(it + 1) == 'o' && *(it + 2) == 'g') {it += 2; st.push(read_special_func("log", sign_operator));}
        else if (*it == 'c' && *(it + 1) == 'o' && *(it + 2) == 's') {it += 2; st.push(read_special_func("cos", sign_operator));}
        else if (*it == 's' && *(it + 1) == 'i' && *(it + 2) == 'n') {it += 2; st.push(read_special_func("sin", sign_operator));}
        else if (*it == 't' && *(it + 1) == 'a' && *(it + 2) == 'n') {it += 2; st.push(read_special_func("tan", sign_operator));}
        else if (*it == 'c' && *(it + 1) == 'o' && *(it + 2) == 't') {it += 2; st.push(read_special_func("cot", sign_operator));}
        else if (*it == 's' && *(it + 1) == 'q' && *(it + 2) == 'r' && *(it + 3) == 't') {it += 3; st.push(read_special_func("sqrt", sign_operator));}
        else if (*it == 'c' && *(it + 1) == 'b' && *(it + 2) == 'r' && *(it + 3) == 't') {it += 3; st.push(read_special_func("cbrt", sign_operator));}
        else if (*it == 'r' && *(it + 1) == 't') {++it; st.push(read_special_func("rt", sign_operator));}
        else if (*it == 'a' && *(it + 1) == 'b' && *(it + 2) == 's') {it += 2; st.push(read_special_func("abs", sign_operator));}
        else if (*it == 'p' && *(it + 1) == 'i') {++it; q.push(read_special_func("pi", sign_operator));}
        else if (*it == 'e') {q.push(read_special_func("e", sign_operator));}
        else if (*it == 'a' && *(it + 1) == 't' && *(it + 2) == 'a' && *(it + 3) == 'n') {it += 3; st.push(read_special_func("atan", sign_operator));}
        else if (*it == 'a' && *(it + 1) == 's' && *(it + 2) == 'i' && *(it + 3) == 'n') {it += 3; st.push(read_special_func("asin", sign_operator));}
        else if (*it == 'a' && *(it + 1) == 'c' && *(it + 2) == 'o' && *(it + 3) == 's') {it += 3; st.push(read_special_func("acos", sign_operator));}
        else if (*it == 'a' && *(it + 1) == 'c' && *(it + 2) == 'o' && *(it + 3) == 't') {it += 3; st.push(read_special_func("acot", sign_operator));}
    }
    while (!st.empty()) { q.push(st.top()); st.pop();}

    double result = equal(q, mode); cout << "Ket qua la : " << result << endl;
    string res = to_string(result); char restemp[res.length() + 1];
    for (int i = 0; i < res.length() - 2; i++) restemp[i] = res[i]; restemp[res.length() - 2] = '\0';
    int count = 1; while (int(result) / 10 != 0) {count++; result /= 10;} if (result < 0) count++;
	outtextxy(630 - count*19, 250, restemp);     
	int yo = 100; moveto(810, yo); cout << "Bieu thuc hau to : "; 
	while(!q.empty()){
        string::iterator it = q.front().begin();
        if(isdigit(*it)){
            for(it = q.front().begin();it != q.front().end();it++){
                if(*it == '.'){ for(int j = 0; j <= 4;j++){ cout << *it; it++;} break;}
                else cout << *it;
            } cout << " ";
        }
        else cout << q.front() << " ";
		char temp[2]; temp[1] = '\0';
		for (int i = 0; i < q.front().length(); i++){
			if (getx() >= 1170){ yo += 25; moveto(810, yo);}
			temp[0] = q.front()[i]; outtext(temp);
		} outtext(" ");	
		q.pop();
	} cout << endl << endl;
}