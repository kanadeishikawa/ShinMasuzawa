# ShinMasuzawa

複数人の審査員が作成した順位表から、新増沢式採点法によって各団体の総合順位を決定するプログラムです。
新増沢式採点法とは、全日本合唱コンクール等で採用されている順位決定方法で、公平かつ信頼度の高い方式と考えられています。
新増沢式採点法の詳細は、[合唱連盟のWebサイト](https://jcanet.or.jp/event/concour/shinmasuzawa-kaisetu201001.htm)を御覧ください。


## 仕様
- 審査員の人数は最大９名までです。審査員数は奇数である必要があります。
- 各審査員は、コンクールに出演した全団体の演奏を審査して、各団体の順位をつけて投票します。この審査表をインプットとして用います。
- 順位づけの際、同率や空位は許されません。出演団体数をNとしたとき、1位からN位までが各団体と1対1に対応するように、すべての順位を重複なくつける必要があります。
- 総合順位を決定する際、過半数の審査員が最上位とする団体が存在しなかった場合、「勝ちポイント」の優劣を総当戦で評価して最上位を決定します。「勝ちポイント」が同点だった場合は、それらの団体のみで「勝ちポイント」の決戦総当たりを行い、なお同点だった場合は「勝ち数」の大きい方を上位とします。「勝ち数」も同点だった場合は、演奏順が最も早かった団体を上位とします。
- プログラムはC++で記述されています。C++をコンパイルして実行できる標準的な環境があれば動作するはずです。
- また、LaTeX/ディレクトリ以下には、結果をまとめるためのLaTeXファイルのサンプルがあります。


## 使用方法
### 審査表の作成
ingiles/ディレクトリに、インプットとなる審査表のファイルを作成します。
サンプルファイルscore_Tohoku_2024.datのように、１行目には団体名をスペースで区切って列挙します。
2行目以降には、各審査員がつけた順位を、１行ずつ、団体名の下部に並ぶようにスペースで区切って入力します。
このサンプル上では審査員数が７名ですから、score_Tohoku_2024.datの行数は８行（団体名１行+審査表７行）となります。

### ソースコードの編集
ShinMasuzawa.ccの中のいくつかの変数を状況によって書き換えてください。
- 14行目のNofJudgeには、審査員の人数を入力してください。
- 15行目のNofSchoolには、出演団体数を入力してください。
- 22行目のListOfSchoolには、各団体名を入力してください。
- 255行目に、インプットとなる審査表のファイル名を入力してください。
- 17行目のflag_displayをtrueにすると、総合順位を算出する際の過程がすべて出力されるようになります。falseにすると、最終結果の総合順位のみが出力されます。

### コンパイル
まず、`mkdir bin`および`mkdir lib`をコマンドを入力してbin/ディレクトリとlib/ディレクトリを作成してください。
次に、`make`とコマンドを打てばコンパイルされ、実行ファイル\bin\ShinMasuzawaが生成されます。

### 実行
- `./bin/ShinMasuzawa`とコマンドを入力すると、プログラムが実行されます。
- flag_displayがfalseの場合、審査表が出力されたあとに、「dai 1 i: Akita Minami」のような形で総合順位が出力されます。
- プログラムが止まってしまうとき
   - 「OVERLAPPING SCORES WERE DETECTED!」と表示された場合、審査表の中に順位の重複があります。Judge No.は、審査表の上から数えて1, 2...となっています。
   - 「A SCORE OUT OF RANGE WAS DETECTED!」と表示された場合、審査表に-1位などのようなおかしな順位があります。

### 順位表の作成
LaTeX\ディレクトリで、`./compile_latex.sh`とコマンド入力すると、Result_Tohoku.texがコンパイルされてResult_Tohoku.pdfが作成されます。


## 著作権
制作者kanade (kanadeishikawa) は、このプログラムの著作権を放棄します。
ご自由にダウンロード・使用・改変・再配布していただいて構いません。
使用する際の連絡は不要です。
