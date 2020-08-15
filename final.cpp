#include<conio.h>
#include<stdio.h>
#include<string>
#include<iostream>

using namespace std;

class Player { //player クラス
	int type; //type0 user ,1 computer
	string name;
	int hand; //手
	int win; //勝敗の数
	int lose;
	int draw;
	int point; //点

public:
	Player(int t, string n)
	{
		type = t;
		name = n;
		win = lose = draw =  point = 0;
	}

	int newHand(void)
	{
		if (type == 0) { //userの手
			cin >> hand; //入力
			return (hand);
		}
		else { //computerの場合
			hand = rand() % 3; //乱数の生成
			return (hand);
		}
	}

	void recordCount(int result) //勝敗の記録
	{
		if (type == 0) { //userの場合
			switch (result) {
			case 0: draw++; break; //case0 u グー,c グー
			case 6: lose++; point = point - 1; break; //case6 u グー,c パー
			case 3: win++; point = point + 3; break; //case3 u グー,c チョキ
			case 4: draw++; break;//case4 u チョキ,c チョキ
			case 1: lose++;  point = point - 2; break;//case1 u チョキ,c グー
			case 7: win++; point = point + 6; break;//case7 u チョキ,c パー
			case 8: draw++; break;//case8 u パー,c パー
			case 5: lose++;  point = point - 2; break;//case5 u パー,c チョキ
			case 2: win++; point = point + 6; break;//case2 u パー,c グー
			}
		}
		if (type == 1) { //computer
			switch (result) {
			case 0: draw++; break;
			case 6: win++; point = point + 3; break;
			case 3: lose++; point = point - 1; break;
			case 4: draw++; break;
			case 1: win++; point = point + 6; break;
			case 7: lose++;  point = point - 2; break;
			case 8: draw++; break;
			case 5: win++; point = point + 6; break;
			case 2: lose++;  point = point - 2; break;
			
			}
		}
	}
	


	

	string getName(void)
	{
		return(name);
	}

	void put_record(void)
	{
		cout << name << ":" << win << "勝" << lose << "負" << draw << "分け " << point << "点\n"; //勝ち負けポイント表示
	}
};

char hd[][7] = { "グー","チョキ","パー" }; //文字配列

void put_jyanken_message(void) { //じゃんけんメッセージ
	cout << "\n\aじゃんけんポン　…　";
	for (int i = 0; i < 3; i++)
		cout << "(" << i << ")" << hd[i] << " "; //グー、チョキ、パーの入力を促す
	cout << ":";
}

void disp_result(int result) //結果の表示（user)
{
	switch (result) {
	case 0: cout << "引き分けです\n"; break; //caseごとにuserの結果表示
	case 6: cout << "You LOSE! -1!\n"; break;
	case 3: cout << "You WIN!! +3!\n"; break;
	case 4: cout << "引き分けです\n"; break;
	case 1: cout << "You LOSE! -2!\n"; break;
	case 7: cout << "You WIN!!!! +6!\n"; break;
	case 8: cout << "引き分けです\n"; break;
	case 5: cout << "You LOSE! -2!\n"; break;
	case 2: cout << "You WIN!!!! +6!\n"; break;
	
	}
}


int confirm_retry(void) //再挑戦するかの確認
{
	int x;
	cout << "retry? (0)いいえ (1)はい"; //0で終了　1で続行
	cin >> x;

	return (x);

}


int main() { 
	int retry;
	Player user(0, "あなた");
	Player comp(1, "敵");

	

	cout << "じゃんけん開始\n";

	do {
		int chand = comp.newHand(); //compの手が決まる
		put_jyanken_message(); //message表示
		int uhand = user.newHand(); //userの手を入力

		cout << user.getName() << "は" << hd[uhand] << "で"
			<< comp.getName() << "は" << hd[chand] << "です\n";

		int a = 3;

		int ujudge = (uhand + (chand * a)); //caseの数字を作る


		int cjudge = (uhand + (chand * a));
		
		disp_result(ujudge); //結果表示

		
		user.recordCount(ujudge); //記録を更新
		comp.recordCount(cjudge);
		user.put_record(); //記録の表示
		comp.put_record();
		

		retry = confirm_retry(); //retryの確認
		
	} while (retry == 1); //retry == 1の間継続


	return(0);//終了
	}