using namespace std;
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

const int NofJudge = 7; // max = 9
const int NofSchool = 24;

const bool flag_display = false; //trueにすると集計過程を表示します。falseにすると総合順位のみ表示します。


//const char ListOfSchool[NofSchool][40] = {"Suginami", "Takamatsu", "Noda", "Kozukata", "Seisen", "Obihiro", "Sagajo", "Gihu", "Moojo", "Ichikawa", "Nagano", "Nagasaki", "Junshin", "Kobe", "Matsue", "Saijo"};

const char ListOfSchool[NofSchool][40] = {"Tagajo", "Hachinohe Kita", "Teikyo Asaka", "Yuzawa", "Ichinoseki Gakuin", "Yamagata Higashi", "Iwaki Yumoto", "Chidoukan", "St. Ursula", "Senshu Kitakami", "Akita Minami", "Hirosaki Chuo", "Izumi Tateyama", "Kurosawajirikita", "Asaka Reimei", "Aomori Yamada", "Meio", "Sogakukan", "Morioka Daiichi", "Iwaki", "Aomori", "Yamagata Chuo", "Sendai Mukaiyama", "Omagari"}; //Tohoku 2024

int KessenTouhyou(int scoretree[][NofSchool], bool flag_kari_1[], int Nofkari1){

  int aka = -9;// 対戦カード
  int ao = -9;// 対戦カード
  int kachi_point[NofSchool] = {};
  int kachi_kazu[NofSchool] = {};

  int val = -1;
  for(int J=0;J<NofSchool;J++){
    if(flag_kari_1[J]==false) continue;

    for(int I=J+1;I<NofSchool;I++){
      if(flag_kari_1[I]==false) continue;

      aka = J;
      ao  = I;
      //ここまでで、対戦組み合わせ赤vs青が決定
      //ここから、多数決での対戦
      int NofWin_aka = 0; //赤の勝利数。青の勝利数は、NofJudge - Nofwin_akaとなる。
      int Junni_aka, Junni_ao;

      for(int J=0;J<NofJudge;J++){
        for(int I=0;I<NofSchool;I++){
          if(scoretree[J][I] == aka) Junni_aka = I;
          if(scoretree[J][I] == ao) Junni_ao = I;
        } //for NofSchool
        if(Junni_aka < Junni_ao) NofWin_aka ++;
      } //for NofJudge

      //赤の勝利数が多ければ、赤の勝ち。青の勝利数が多ければ、青の勝ち
      if(NofWin_aka > NofJudge/2){
        kachi_point[aka] ++;
      } //if
      else{
        kachi_point[ao] ++;
      } //else

    } //for I
  } //for J

  //勝ちポイントが最も多い学校が決戦投票の勝者
  int max_kachi_point = -1;
  int count_max_kachi = 0;
  int win_school = -1;
  for(int J=0;J<NofSchool;J++){
    if(kachi_point[J]>max_kachi_point){
      max_kachi_point = kachi_point[J];
    } //if
  } //for

  for(int J=0;J<NofSchool;J++){
    if(kachi_point[J] == max_kachi_point){
      count_max_kachi ++;
      win_school = J;
    } //if
  } //for

  //cout
  if(flag_display == true){
    for(int J=0;J<NofSchool;J++){
      if(flag_kari_1[J] == true){
        cout << setw(17) << ListOfSchool[J] << " winning point: " << setw(2) << kachi_point[J] << endl;
      } //if
    } //for
  } //if

  //returnする値
  if(count_max_kachi == 1){
    val = win_school;
    if(flag_display == true){
      cout << "  --> the winner is " << ListOfSchool[win_school] << endl;
    } //if
  } //if

  //もし勝ちポイントが同点で並んだ場合、勝ちポイント１位の学校だけで勝負する
  else if(count_max_kachi > 1){
    if(flag_display == true){
      cout << "There are schools tied for first place with the same winning points!" << endl;
      cout << "We will compare those schools with each other." << endl;
    } //if

    bool flag_kessen[NofSchool] = {};
    for(int J=0;J<NofSchool;J++){
      if(flag_kari_1[J] == true && kachi_point[J] == max_kachi_point){
        flag_kessen[J] = true;
      } //if
      else{
        flag_kessen[J] = false;
      } //else
    } //for
  
    aka = -9;// 対戦カード
    ao = -9;// 対戦カード

    for(int J=0;J<NofSchool;J++){
      kachi_point[J] = 0;
      kachi_kazu[J] = 0;
    } //for

    for(int J=0;J<NofSchool;J++){
      if(flag_kessen[J]==false) continue;

      for(int I=J+1;I<NofSchool;I++){
        if(flag_kessen[I]==false) continue;

        aka = J;
        ao  = I;
        //ここまでで、対戦組み合わせ赤vs青が決定
        //ここから、多数決での対戦
        int NofWin_aka = 0; //赤の勝利数。青の勝利数は、NofJudge - Nofwin_akaとなる。
        int Junni_aka, Junni_ao;

        for(int J=0;J<NofJudge;J++){
          for(int I=0;I<NofSchool;I++){
            if(scoretree[J][I] == aka) Junni_aka = I;
            if(scoretree[J][I] == ao) Junni_ao = I;
          } //for NofSchool
          if(Junni_aka < Junni_ao){
            NofWin_aka ++;
            kachi_kazu[aka] ++;
          } //if
          else{
            kachi_kazu[ao] ++;
          } //else
        } //for NofJudge

        //赤の勝利数が多ければ、赤の勝ち。青の勝利数が多ければ、青の勝ち
        if(NofWin_aka > NofJudge/2){
          kachi_point[aka] ++;
        } //if
        else{
          kachi_point[ao] ++;
        } //else

      } //for I
    } //for J

    //勝ちポイントが最も多い学校が決戦投票の勝者
    int max_kachi_point = 0;
    int count_max_kachi = 0;
    int win_school = -1;
    for(int J=0;J<NofSchool;J++){
      if(kachi_point[J]>max_kachi_point){
        max_kachi_point = kachi_point[J];
      } //if
    } //for

    for(int J=0;J<NofSchool;J++){
      if(kachi_point[J] == max_kachi_point){
        count_max_kachi ++;
        win_school = J;
      } //if
    } //for

    //cout
    if(flag_display == true){
      for(int J=0;J<NofSchool;J++){
        if(flag_kari_1[J] == true){
          cout << setw(17) << ListOfSchool[J] << " winning point: " << setw(2) << kachi_point[J] << endl;
        } //if
      } //for
    } //if


    //returnする値
    if(count_max_kachi == 1){
      val = win_school;
      if(flag_display == true){
        cout << "  --> the winner is " << ListOfSchool[win_school] << endl;
      } //if
    } //if

    //それでも勝ちポイント１位が複数の場合、勝ち数が最も大きい学校が勝利
    else if(count_max_kachi > 1){

      if(flag_display == true){
        cout << "There are still multiple schools tied for first place in winning points!" << endl;
        cout << " In this case, the school with the most wins will be the winner." << endl;
      } //if
      int school_max_kachikazu = -1;
      int max_kachikazu = -1;
      int number_of_max_kachikazu = 0;
      for(int J=0;J<NofSchool;J++){
        if(kachi_kazu[J] > max_kachikazu) max_kachikazu = kachi_kazu[J];
      } //for
      for(int J=0;J<NofSchool;J++){
        if(kachi_kazu[J] == max_kachikazu){
          number_of_max_kachikazu ++;
          school_max_kachikazu = J;
        } //if
      } //for

      //勝ち数１位が１校の場合
      if(number_of_max_kachikazu == 1){
        win_school = school_max_kachikazu;
      } //if
      //勝ち数１位が複数校の場合
      //最も演奏順が早かった学校が勝利（これは私の価値観によるものです）
      else{
        for(int J=0;J<NofSchool;J++){
          if(kachi_kazu[J] == max_kachikazu){
            win_school = J;
            break;
          } //if
        } //for
      } //else

      //cout
      if(flag_display == true){
        for(int J=0;J<NofSchool;J++){
          if(flag_kessen[J] == true){
            cout << setw(17) << ListOfSchool[J] << " number of wins: " << setw(2) << kachi_kazu[J] << endl;
          } //if
        } //for
        cout << "  --> the winner is " << ListOfSchool[win_school] << endl;
      } //if

      val = win_school;
    } //else if

  } //else if (count_max_kachi > 1)

  return val;

} //KessenTouhyou

int main(){


  //read file
  //ifstream ifs("./infiles/score_sample.dat");
  ifstream ifs("./infiles/score_Tohoku_2024.dat");
  if (ifs.fail()) {
     cerr << "Cannot open file\n";
     exit(0);
  }
  string str;
  int score[NofSchool] = {};
  int scoretree[NofJudge][NofSchool] = {}; // scoretree[審査員ID][順位] value=School ID
  int J = 0; //行カウンター

  int outputtree[NofJudge][NofSchool] = {}; //outputtree[審査員ID][学校ID] value = 順位
                                            //display表示専用

  while (getline(ifs,str)) {
    stringstream ss(str);
    string item;
    int index = 0; //列カウンター

    while(ss >> item && index < NofSchool+1){
      if(J != 0) score[index] = stoi(item);
      index ++;
    } //while

    for(int I=0;I<NofSchool;I++){
      if(J != 0){
        scoretree[J-1][score[I]-1] = I;
        outputtree[J-1][I] = score[I]-1;
      } //if
    }
    J++;
  } //while

  bool flag_stop = false;
  for(int I=0;I<NofJudge;I++){
    for(int J=0;J<NofSchool;J++){
      for(int JJ=J+1;JJ<NofSchool;JJ++){
        if(outputtree[I][J] == outputtree[I][JJ] && outputtree[I][J] != -999){
          cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
          cout << "OVERLAPPING SCORES WERE DETECTED!" << endl;
          cout << "IN Judge No. " << I+1 << ", RANK OF " << ListOfSchool[J]  << " AND " << ListOfSchool[JJ] << " ARE SAME: " << outputtree[I][J]+1 << endl;
          cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
          flag_stop = true;
        } //if

      } //for JJ

      if(outputtree[I][J] < 0 || outputtree[I][J] >= NofSchool){
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        cout << "A SCORE OUT OF RANGE WAS DETECTED!" << endl;
        cout << "IN Judge No. " << I+1 << ", RANK OF " << ListOfSchool[J] << " IS OUT OF RANGE: " << outputtree[I][J]+1 << endl;
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        flag_stop = true;
      } //if
    } //for J
  } //for I
  if(flag_stop == true) return -1;



  int count_junni = 1;
  while(count_junni <= NofSchool){

    if(flag_display == true || count_junni==1){
      if(flag_display == true) cout << "=======================================" << endl;
      cout << "                  ";
      for(int J=0;J<NofJudge;J++){
        cout << "Judge" << setw(2) << J+1 << " ";
      } // for
      cout << endl;

      for(int I=0;I<NofSchool;I++){
        cout << setw(17) << ListOfSchool[I] << " ";
        for(int J=0;J<NofJudge;J++){
          if(outputtree[J][I] != -999) cout << setw(7) << outputtree[J][I]+1 << " ";
          else  cout << "        ";
          //cout << scoretree[J][I] << " ";
        } //for
      cout << endl;
      } //for
    } //if

    //順位表で、各審査員の最上位校をリストアップする
    int vote[NofSchool] = {};
    for(J=0;J<NofJudge;J++){
      bool flag_vote = true;

      int I = 0;
      while(flag_vote == true){
        if(scoretree[J][I] == -999){
          I ++;
        } //if
        else{
          flag_vote = false;
          vote[scoretree[J][I]] ++;
        } //else
      } //while

    } //for

    int kakutei = -999; //最上位順位確定校

    //ステップ１：過半数得票の１校はあるか？
    for(J=0;J<NofSchool;J++){
      if(((double) vote[J]) > ((double) NofJudge/2)){
        if(flag_display == true){
          cout << "Case 1: There is a school that has won the majority of first-place votes!" << endl;
        } //if
      kakutei = J;
      } //if
    } //for

    //ステップ２：過半数得票の１校がない場合
    //最大得票数と２番めの得票数は？
    int ichiban_tokuhyou = 0;
    int niban_tokuhyou = 0;
    for(J=0;J<NofSchool;J++){
      if(vote[J] > ichiban_tokuhyou){
        ichiban_tokuhyou = vote[J];
      } //if
    } //for

    for(J=0;J<NofSchool;J++){
      if(vote[J] > niban_tokuhyou && vote[J] < ichiban_tokuhyou){
        niban_tokuhyou = vote[J];
      } //if
    } //for


    //最大得票を得た学校は？(仮の１位)
    bool flag_kari_1[NofSchool] = {};
    for(J=0;J<NofSchool;J++){
      flag_kari_1[J] = false;
    } //for

    int Nofkari1 = 0;
    for(J=0;J<NofSchool;J++){
      if(vote[J] == ichiban_tokuhyou){
        flag_kari_1[J] = true;
        Nofkari1 ++;
      } //if
      else{
        flag_kari_1[J] = false;
      } //else
    } //for

    //２番めの得票を得た学校は？(仮の２位)
    bool flag_kari_2[NofSchool] = {};
    for(J=0;J<NofSchool;J++){
      flag_kari_2[J] = false;
    } //for

    int Nofkari2 = 0;
    for(J=0;J<NofSchool;J++){
      if(vote[J] == niban_tokuhyou){
        flag_kari_2[J] = true;
        Nofkari2 ++;
      } //if
      else{
        flag_kari_2[J] = false;
      } //else
    } //for


    //仮の１位が複数で、獲得票合計が過半数のとき、仮の１位どうしでの総当たりで決める
    if(Nofkari1 > 1 && ((double) ichiban_tokuhyou*Nofkari1) > ((double) NofJudge/2)){
      if(flag_display == true){
        cout << "Case 2: There are multiple <<provisional first-place>> candidates, and together they hold the majority of votes!" << endl;
        cout << "        A round-robin among these candidates will determine the final first-place winner." << endl;
      } //if
      kakutei = KessenTouhyou(scoretree, flag_kari_1, Nofkari1);
    } // if

    //仮の１位の合計得票数が過半数に満たないとき、仮の１位と仮の２位での総当たりで決める
    else if(((double) ichiban_tokuhyou*Nofkari1) < ((double) NofJudge/2) && ((double) ichiban_tokuhyou*Nofkari1 + niban_tokuhyou*Nofkari2) > ((double) NofJudge/2)){
      if(flag_display == true){
        cout << "Case 3: The total votes for the <<provisional first-place>> candidates do not reach a majority!" << endl;
        cout << "        A round-robin between (among) the <<provisional first-place>> and <<provisional second-place>> candidates will determine the final first-place winner." << endl;
      } //if
      //仮の２位が１校の場合
      if(Nofkari2 == 1){
        if(flag_display == true){
          cout << "Case 3-1: The <<provisional second place>> is held by one school = ";
        } //if
        for(J=0;J<NofSchool;J++){
          if(flag_kari_2[J] == true){
            Nofkari1 ++;
            flag_kari_1[J] = true;
            if(flag_display == true){
              cout << ListOfSchool[J] << endl;;
            } //if
          } //if
        } //for

        kakutei = KessenTouhyou(scoretree, flag_kari_1, Nofkari1);
      } //if

      //仮の２位が複数校の場合、まず仮の２位のどうしで予選の総当たりを行なって、勝ち残った１校と仮の１位どうしで決勝総当たりをする
      else if(Nofkari2 > 1){
        if(flag_display == true){
          cout << "Case 3-2: There are multiple <<provisional second-place>> schools!" << endl;
          cout << "          In this case, a round-robin among the <<provisional second-place>> schools will determine the one remaining school." << endl;
        } //if
 
        int yosen_tsuuka_kari2 = KessenTouhyou(scoretree, flag_kari_2, Nofkari2);
        Nofkari1 ++;
        flag_kari_1[yosen_tsuuka_kari2] = true;
        if(flag_display == true){
          cout << "Next, a round-robin among the <<provisional first-place>> schools and the remaining <<provisional second-place>> school will determine the final first-place winner." << endl;
        } //if
        kakutei = KessenTouhyou(scoretree, flag_kari_1, Nofkari1);
    for(int I=0;I<NofSchool;I++){
        
    } //for
      } //else if

    } //else if

    //ここまでで、最上位校が確定(kakutei)
    //順位表からその団体を削除する
    for(int J=0;J<NofJudge;J++){
      for(int I=0;I<NofSchool;I++){
        if(scoretree[J][I] == kakutei){
          scoretree[J][I] = -999;
          outputtree[J][kakutei] = -999;
        } //if
      } //for
    } //for

    cout << "dai " << count_junni << " i: " << ListOfSchool[kakutei] << endl;
    count_junni ++;

  } //while count_junni <= NofSchool

  cout << "Well done!" << endl;
  return 0;

}
