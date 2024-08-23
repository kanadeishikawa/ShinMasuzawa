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

const bool flag_display = true; //trueにすると集計過程を表示します。falseにすると総合順位のみ表示します。

const int chair = 1; //審査員長の順位は審査表の最も上に記載


int KessenTouhyou(const int NofSchool, const int NofJudge, const vector<vector<int>> scoretree, const vector<bool> flag_kari_1, const int Nofkari1, const vector<string> ListOfSchool){

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
  } //if count_max_kachi == 1

  //もし勝ちポイントが同点で並んだ場合、勝ちポイント１位の学校だけで勝負する
  else if(count_max_kachi > 1){

    int initial_count_max_kachi = count_max_kachi;
    bool flag_saido = true;
    while(flag_saido == true){

      if(flag_display == true){
        cout << "winning points ga douten desu!" << endl;
        cout << "sorera no dantai nomi de saido hikaku shimasu." << endl;
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

      for(int J=0;J<NofSchool;J++){
        kachi_point[J] = 0; //initialize
        kachi_kazu[J] = 0; //initialize
      } //for
    
      aka = -9;// 対戦カード
      ao = -9;// 対戦カード

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
      max_kachi_point = 0;
      count_max_kachi = 0;
      int win_school = -1;
      for(int J=0;J<NofSchool;J++){
        if(kachi_point[J]>max_kachi_point){
          max_kachi_point = kachi_point[J]; //max_kachi_point更新
        } //if
      } //for

      for(int J=0;J<NofSchool;J++){
        if(kachi_point[J] == max_kachi_point){
          count_max_kachi ++; //count_max_kachi更新
          win_school = J;
        } //if
      } //for

      //cout
      if(flag_display == true){
        for(int J=0;J<NofSchool;J++){
          if(flag_kessen[J] == true){
            cout << setw(17) << ListOfSchool[J] << " winning point: " << setw(2) << kachi_point[J] << endl;
          } //if
        } //for
      } //if

      //returnする値
      if(count_max_kachi == 1){
        flag_saido = false; //whileはもう繰り返さない
        val = win_school;
        if(flag_display == true){
          cout << "  --> the winner is " << ListOfSchool[win_school] << endl;
        } //if
      } //if

      //再度の総当たりの１位が複数校いるけど、脱落校もいる場合
      else if(count_max_kachi > 1 && count_max_kachi != initial_count_max_kachi){

        flag_saido = true; //whileを再度繰り返す
        initial_count_max_kachi = count_max_kachi;

      } //else if count_max_kachi > 1 && count_max_kachi != initial_count_max_kachi

      //再度の総当たりの１位が複数校いて、脱落校がいない場合
      else if(count_max_kachi > 1 && count_max_kachi == initial_count_max_kachi){

        flag_saido = false; //whileはもう繰り返さない

        if(flag_display == true){
          cout << "mata douten desu!!" << endl;
          cout << "number of wins ga ooi dantai ga kachi desu" << endl;
        } //if

        //勝ち数が最も大きい学校が勝利
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
  
        if(flag_display == true){
          for(int J=0;J<NofSchool;J++){
            if(flag_kessen[J] == true){
              cout << setw(17) << ListOfSchool[J] << " number of wins: " << setw(2) << kachi_kazu[J] << endl;
            } //if
          } //for
        } //if
  
        //勝ち数１位が１校の場合
        if(number_of_max_kachikazu == 1){
          win_school = school_max_kachikazu;
        } //if
        //勝ち数１位が複数校の場合
        //審査員長が最上位とした団体を選出
        else{
          bool flag_kessen2[NofSchool] = {};
          for(int J=0;J<NofSchool;J++){
            if(flag_kessen[J] == true && kachi_kazu[J] == max_kachikazu){
              flag_kessen2[J] = true;
            } //if
            else{
              flag_kessen2[J] = false;
            } //else
          } //for
  
          if(flag_display == true){
            cout << "number of wins mo douten desu!!!" << endl;
            cout << "shinsa-incho (Judge " << chair << ") no junni de kimemasu" << endl;
            for(int J=0;J<NofSchool;J++){
              if(flag_kessen2[scoretree[chair-1][J]] == true){
                cout << setw(17) << ListOfSchool[scoretree[chair-1][J]] << " shinsa-incho no junni: " << setw(2) << J+1 << endl;
              } //if
            } //for
          } //if
  
          int best_junni = 999;
          for(int J=0;J<NofSchool;J++){
            if(flag_kessen2[scoretree[chair-1][J]] == true && scoretree[chair-1][J] < best_junni){
              best_junni = scoretree[chair-1][J];
            } //if
          } //for
          win_school = best_junni;
  
        } //else
  
        //cout
        if(flag_display == true){
          cout << "  --> the winner is " << ListOfSchool[win_school] << endl;
        } //if
  
        val = win_school;

      } //else if count_max_kachi > 1 && count_max_kachi == initial_count_max_kachi
    } //while flag_saido == true

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
  int row_count = 0; //行カウンター0はじまり

  int NofSchool;
  int NofSchool_save;
  int NofJudge;

  vector<string> ListOfSchool;
  vector<int> score;
  vector<vector<int>> scoretree;   // scoretree[審査員ID][順位] value=School ID
  vector<vector<int>> outputtree;  //outputtree[審査員ID][学校ID] value = 順位  display表示専用

  while (getline(ifs,str)) {
    stringstream ss(str);
    string item;

    score.clear();

    while(ss >> item){

      //1行目
      if(row_count == 0){
        ListOfSchool.push_back(item);
      } //if

      //2行目以降
      if(row_count != 0){
        score.push_back(stoi(item));
      } //if
    } //while

    NofSchool_save = ListOfSchool.size();
    NofSchool = score.size();

    if(row_count != 0 && NofSchool != NofSchool_save){
      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
      cout << "The number of elements per line does not match!" << endl;
      cout << "The strange row number = " << row_count+1 << "." << endl;
      cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
      return -1;
    } //if

    if(row_count != 0){
      outputtree.push_back(score); //ひとまず１行分の値をfillする
      scoretree.push_back(score); //ひとまず１行分の値をfillする
      for(int i=0;i<NofSchool;i++){
        outputtree[row_count-1][i] = outputtree[row_count-1][i] - 1; //これが正しい値
        scoretree[row_count-1][score[i]-1] = i; //これが正しい値
      }  //for
    } //if

    row_count ++;
  } //while

  NofJudge = row_count-1;

  if(NofJudge < chair){
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    cout << "Chair's number is strange!" << endl;
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    return -1;
  } //if

  if(NofJudge%2 == 0){
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    cout << "Number of Judges must be odd!" << endl;
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    return -1;
  } //if

  bool flag_stop = false;
  for(int I=0;I<NofJudge;I++){
    for(int J=0;J<NofSchool;J++){
      for(int JJ=J+1;JJ<NofSchool;JJ++){
        if(outputtree[I][J] == outputtree[I][JJ] && outputtree[I][J] != -999 && flag_stop == false){
          cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
          cout << "OVERLAPPING SCORES WERE DETECTED!" << endl;
          cout << "IN Judge No. " << I+1 << ", RANK OF " << ListOfSchool[J]  << " AND " << ListOfSchool[JJ] << " ARE SAME: " << outputtree[I][J]+1 << endl;
          cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
          flag_stop = true;
        } //if

      } //for JJ

      if((outputtree[I][J] < 0 || outputtree[I][J] >= NofSchool) && flag_stop == false){
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
  cout << "<<< The chair is Judge" << setw(2) << chair << " >>>" << endl;
  while(count_junni <= NofSchool){


    if(flag_display == true || count_junni==1){
      if(flag_display == true) cout << "=======================================" << endl;
      cout << "                  ";
      for(int J=0;J<NofJudge;J++){
        cout << "Judge" << setw(2) << J+1 << "  ";
      } // for
      cout << endl;

      for(int I=0;I<NofSchool;I++){
        cout << setw(17) << ListOfSchool[I] << " ";
        for(int J=0;J<NofJudge;J++){
          if(outputtree[J][I] != -999) cout << setw(7) << outputtree[J][I]+1 << "  ";
          else  cout << "         ";
        } //for
      cout << endl;
      } //for
    } //if

    //順位表で、各審査員の最上位校をリストアップする
    //int vote[NofSchool] = {};
    vector<int> vote;
    vector<int> vote_sort;
    for(int J=0;J<NofSchool;J++){
      vote.push_back(0); //initialize
      vote_sort.push_back(0); //initialize
    } //for

    for(int J=0;J<NofJudge;J++){
      bool flag_vote = true;

      int I = 0;
      while(flag_vote == true){
        if(scoretree[J][I] == -999){
          I ++;
        } //if
        else{
          flag_vote = false;
          vote[scoretree[J][I]] ++;
          vote_sort[scoretree[J][I]] ++;
        } //else
      } //while

    } //for

    std::sort(vote_sort.begin(), vote_sort.end(), greater<int>());

    int kakutei = -999; //最上位順位確定校

    vector<int> kari_ni_vote;
    vector<int> NofSchool_kari_ni_vote;
    for(int J=0;J<NofSchool;J++){
        kari_ni_vote.push_back(0); //initialize
        NofSchool_kari_ni_vote.push_back(0); //initialize
    } //for

    int vote_tmp = -999;
    int count_tmp = 0;
    for(int J=0;J<NofSchool;J++){
      //cout << "vote_sort[" << J << "] = " << vote_sort[J] << endl;
      if(vote_tmp != vote_sort[J]){
          kari_ni_vote[count_tmp] = vote_sort[J];
          vote_tmp = vote_sort[J];
          //cout << "kari_ni_vote[" << count_tmp << "] = " << kari_ni_vote[count_tmp] << endl;
          count_tmp ++;
      } //if
    } //for

    //kari_ni_vote[0]: 仮の第１位の得票数
    //kari_ni_vote[1]: 仮の第２位の得票数
    //kari_ni_vote[2]: 仮の第３位の得票数 ... と続く

    for(int R=0;R<kari_ni_vote.size();R++){
      //cout << "kari_ni_vote[" << R << "] : " << kari_ni_vote[R] << endl;
    } //for

    for(int J=0;J<NofSchool;J++){
      for(int i=0;i<NofSchool;i++){
        if(kari_ni_vote[J] > 0 && vote[i] == kari_ni_vote[J]){
          NofSchool_kari_ni_vote[J] ++;
        } //if
      } //for
    } //for

    //NofSchool_kari_ni_vote[0]: 仮の第１位の得票数を得た学校の数
    //NofSchool_kari_ni_vote[1]: 仮の第２位の得票数を得た学校の数
    //NofSchool_kari_ni_vote[2]: 仮の第３位の得票数を得た学校の数 ... と続く


    bool flag_loop = false;
    int kari_junni = 0;

    while(flag_loop != true){ //過半数に達するまでループする

      //第(kari_junni+1)位までの団体で、過半数に達するか？
      int NofVote = 0;
      for(int j=0;j<=kari_junni;j++){
        NofVote = NofVote + NofSchool_kari_ni_vote[j]*kari_ni_vote[j];
      } //for

      if(NofVote > (int) NofJudge/2){
        if(flag_display ==true){
           cout << "kari no " << kari_junni+1 << " i made de kahannsuu!" << endl;
           for(int i=0;i<=kari_junni;i++){
             for(int j=0;j<NofSchool;j++){
               if(vote[j] == kari_ni_vote[i]) cout << "   kari no " << i+1 << " i : " << ListOfSchool[j] 
                                                            << ", number of votes is " << vote[j] << endl;
             } //for j
           } //for i
        } //if flag_display ==true

        int SelectedSchool = -999;

        for(int i=kari_junni;i>=0;i--){ //仮の順位が大きい方から始める

          vector<bool> flag_kari_junni;
          int NofSchool_kari_junni = 0;
          for(int j=0;j<NofSchool;j++){
            if(vote[j] == kari_ni_vote[i]){
              flag_kari_junni.push_back(true);
              NofSchool_kari_junni ++;
            } //if
            else{
              flag_kari_junni.push_back(false);
            } //else
          } //for j

          if(SelectedSchool != -999){
            flag_kari_junni[SelectedSchool] = true;
            NofSchool_kari_junni ++;
          } //if


          if(flag_display == true){
            cout << "kari no " << i+1 << " i wo kangaemasu" << endl;
          } //if

          if(NofSchool_kari_junni == 1){  //仮の第(kari_junni +1)位の学校が１校の場合
            for(int j=0;j<NofSchool;j++){
              if(vote[j] == kari_ni_vote[i]) SelectedSchool = j;
            } //for j
            if(flag_display == true){
              cout << "   --> " << ListOfSchool[SelectedSchool] << " ga erabare mashita" << endl;
            } //if

          } //if

          else{  //仮の第(kari_junni +1)位の学校が複数校の場合 同順位内で決選投票

            SelectedSchool = KessenTouhyou(NofSchool, NofJudge, scoretree, flag_kari_junni, NofSchool_kari_junni, ListOfSchool);
          } //else
          
          if(i == 0){
            kakutei = SelectedSchool;
            flag_loop = true;
          } //if
        } //for i

      } //if 過半数

      //過半数に達しない場合
      else{
        kari_junni ++;
      } //else
    } //while

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

  } //while count_junni <= NofSchoo

  cout << "Well done!" << endl;
  return 0;

}
