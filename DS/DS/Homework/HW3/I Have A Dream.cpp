#define DSA_STACK_VECTOR //使用基于向量的栈
#include<cstdio>//引用c模式精确控制输入输出流
#include<iostream>//引用标准输入输出流
#include"HuffmanTree.h"//引用栈

using namespace std;
int* statistics(char* text)//统计字符出现频率 
{
    char* ch = text;
    int* freq = new int[N_CHAR];  //以下统计需随机访问，故以数组记录各字符出现次数
    memset(freq, 0, sizeof(int) * N_CHAR); //清零
    for (; *ch != '\0'; ch++) //逐个记录每个字符出现次数
    {
        if (*ch >= 0x20)
        {
            freq[*ch - 0x20]++; //累计对应的出现次数
        }
    }
    return freq;
}
HuffForest* initForest(int* freq)//根据频率统计表，为每个字符创建一棵树
{ 
    HuffForest* forest = new HuffForest; //以List实现的Huffman森林
    for (int i = 0; i < N_CHAR; i++) //为每个字符
    { 
        forest->insertAsLast(new HuffTree); //生成一棵树，并将字符及其频率
        forest->last()->data->insertAsRoot(HuffChar(0x20 + i, freq[i])); //存入其中
    }
    return forest;
}
HuffTree* minHChar(HuffForest* forest)//在Huffman森林中找出权重最小的Huffman字符
{ 
    ListNodePosi<HuffTree*> m = forest->first(); //从首节点出发，遍历所有节点
    for (ListNodePosi<HuffTree*> p = m->succ; forest->valid(p); p = p->succ)
    {
        if (m->data->root()->data.weight > p->data->root()->data.weight) //不断更新
        {
            m = p; //找到最小节点（所对应的Huffman子树）
        }
    }
    return forest->remove(m); //从森林中取出该子树，并返回
}
HuffTree* generateTree(HuffForest* forest) //Huffman编码算法
{
    while (1 < forest->size())
    {
        HuffTree* T1 = minHChar(forest); HuffTree* T2 = minHChar(forest);
        HuffTree* S = new HuffTree();
        S->insertAsRoot(HuffChar('^', T1->root()->data.weight + T2->root()->data.weight));
        S->attachAsLC(S->root(), T1);
        S->attachAsRC(S->root(), T2);
        forest->insertAsLast(S);
    } //assert: 循环结束时，森林中唯一（列表首节点中）的那棵树即Huffman编码树
    return forest->first()->data;
}
static void generateCT (Bitmap* code, int length, HuffTable* table, BinNodePosi <HuffChar> v)//通过遍历获取各字符的编码
{
    if (IsLeaf(*v)) //若是叶节点
    {
        table->put(v->data.ch, code->bits2string(length)); 
        return;
    }
    if (HasLChild(*v)) //Left = 0
    {
        code->clear(length); 
        generateCT(code, length + 1, table, v->lc);
    }
    if (HasRChild(*v)) //Right = 1
    {
        code->set(length); 
        generateCT(code, length + 1, table, v->rc);
    }
}
HuffTable* generateTable(HuffTree* tree) //将各字符编码统一存入以散列表实现的编码表中
{ 
    HuffTable* table = new HuffTable; Bitmap* code = new Bitmap;
    generateCT(code, 0, table, tree->root()); release(code); return table;
};
int encode(HuffTable* table, Bitmap* codeString, char* s) //按照编码表对Bitmap串编码
{ 
    int n = 0; //待返回的编码串总长n
    for (size_t m = strlen(s), i = 0; i < m; i++) //对于明文中的每个字符
    {
        char** pCharCode = table->get(s[i]); //取出其对应的编码串
        if (!pCharCode) pCharCode = table->get(s[i] + 'A' - 'a'); //小写字母转为大写
        if (!pCharCode) pCharCode = table->get(' '); //无法识别的字符统一视作空格
        printf("%s", *pCharCode); //输出当前字符的编码
        for (size_t m = strlen(*pCharCode), j = 0; j < m; j++) //将当前字符的编码接入编码串
            '1' == *(*pCharCode + j) ? codeString->set(n++) : codeString->clear(n++);
    }
    printf("\n");
    return n;
} //二进制编码串记录于位图codeString中
void decode(HuffTree* tree, Bitmap* code, int n) 
{
    BinNodePosi<HuffChar> x = tree->root();
    for (int i = 0; i < n; i++) 
    {
        x = code->test(i) ? x->rc : x->lc;
        if (IsLeaf(*x)) 
        {
            printf("%c", x->data.ch);
            x = tree->root(); 
        }
    }
} //解出的明码，在此直接打印输出

int main() //I Have A Dream
{ 
    char I_Have_A_Dream[10000] = { "I am happy to join with you today in what will go down in history as the greatest demonstration for freedom in the history of our nation.Five score years ago, a great American, in whose symbolic shadow we stand today, signed the Emancipation Proclamation.This momentous decree came as a great beacon light of hope to millions of Negro slaves who had been seared in the flames of withering injustice.It came as a joyous daybreak to end the long night of bad captivity.But one hundred years later, the Negro still is not free.One hundred years later, the life of the Negro is still sadly crippled by the manacles of segregation and the chains of discrimination.One hundred years later, the Negro lives on a lonely island of poverty in the midst of a vast ocean of material prosperity.One hundred years later, the Negro is still languished in the corners of American society and finds himself an exile in his own land.And so we've come here today to dramatize a shameful condition.In a sense we've come to our nation's capital to cash a check.When the architects of our republic wrote the magnificent words of the Constitution and the Declaration of Independence, they were signing a promissory note to which every American was to fall heir.This note was a promise that all men, yes, black men as well as white men, would be guaranteed the 'unalienable Rights of Life, Liberty and the pursuit of Happiness.' It is obvious today that America has defaulted on this promissory note, insofar as her citizens of color are concerned.Instead of honoring this sacred obligation, America has given the Negro people a bad check, a check which has come back marked 'insufficient funds.'But we refuse to believe that the bank of justice is bankrupt.We refuse to believe that there are insufficient funds in the great vaults of opportunity of this nation.And so, we've come to cash this check, a check that will give us upon demand the riches of freedom and the security of justice.We have also come to this hallowed spot to remind America of the fierce urgency of Now.This is no time to engage in the luxury of cooling off or to take the tranquilizing drug of gradualism.Now is the time to make real the promises of democracy.Now is the time to rise from the dark and desolate valley of segregation to the sunlit path of racial justice.Now is the time to lift our nation from the quicksands of racial injustice to the solid rock of brotherhood.Now is the time to make justice a reality for all of God's children.It would be fatal for the nation to overlook the urgency of the moment.This sweltering summer of the Negro's legitimate discontent will not pass until there is an invigorating autumn of freedom and equality. Nineteen sixty-three is not an end, but a beginning. And those who hope that the Negro needed to blow off steam and will now be content will have a rude awakening if the nation returns to business as usual. And there will be neither rest nor tranquility in America until the Negro is granted his citizenship rights. The whirlwinds of revolt will continue to shake the foundations of our nation until the bright day of justice emerges.But there is something that I must say to my people, who stand on the warm threshold which leads into the palace of justice : In the process of gaining our rightful place, we must not be guilty of wrongful deeds.Let us not seek to satisfy our thirst for freedom by drinking from the cup of bitterness and hatred.We must forever conduct our struggle on the high plane of dignity and discipline.We must not allow our creative protest to degenerate into physical violence.Again and again, we must rise to the majestic heights of meeting physical force with soul force.The marvelous new militancy which has engulfed the Negro community must not lead us to a distrust of all white people, for many of our white brothers, as evidenced by their presence here today, have come to realize that their destiny is tied up with our destiny.And they have come to realize that their freedom is inextricably bound to our freedom.We cannot walk alone.And as we walk, we must make the pledge that we shall always march ahead.We cannot turn back.There are those who are asking the devotees of civil rights, 'When will you be satisfied?' We can never be satisfied as long as the Negro is the victim of the unspeakable horrors of police brutality.We can never be satisfied as long as our bodies, heavy with the fatigue of travel, cannot gain lodging in the motels of the highways and the hotels of the cities.We cannot be satisfied as long as the Negro's basic mobility is from a smaller ghetto to a larger one. We can never be satisfied as long as our children are stripped of their selfhood and robbed of their dignity by signs stating 'for whites only.' We cannot be satisfied as long as a Negro in Mississippi cannot vote and a Negro in New York believes he has nothing for which to vote. No, no, we are not satisfied, and we will not be satisfied until 'justice rolls down like waters, and righteousness like a mighty stream.'I am not unmindful that some of you have come here out of great trials and tribulations.Some of you have come fresh from narrow jail cells.And some of you have come from areas where your quest -- quest for freedom left you battered by the storms of persecution and staggered by the winds of police brutality.You have been the veterans of creative suffering.Continue to work with the faith that unearned suffering is redemptive.Go back to Mississippi, go back to Alabama, go back to South Carolina, go back to Georgia, go back to Louisiana, go back to the slums and ghettos of our northern cities, knowing that somehow this situation can and will be changed.Let us not wallow in the valley of despair, I say to you today, my friends.And so even though we face the difficulties of today and tomorrow, I still have a dream.It is a dream deeply rooted in the American dream.I have a dream that one day this nation will rise up and live out the true meaning of its creed : 'We hold these truths to be self-evident, that all man are created equal.'I have a dream that one day on the red hills of Georgia, the sons of former slaves and the sons of former slave owners will be able to sit down together at the table of brotherhood.I have a dream that one day even the state of Mississippi, a state sweltering with the heat of injustice, sweltering with the heat of oppression, will be transformed into an oasis of freedom and justice.I have a dream that my four little children will one day live in a nation where they will not be judged by the color of their skin but by the content of their character.I have a dream today!I have a dream that one day, down in Alabama, with its vicious racists, with its governor having his lips dripping with the words of 'interposition' and 'nullification' --one day right there in Alabama little black boys and black girls will be able to join hands with little white boys and white girls as sisters and brothers.I have a dream today!I have a dream that one day every valley shall be exalted, and every hill and mountain shall be made low, the rough places will be made plain, and the crooked places will be made straight; 'and the glory of the Lord shall be revealed and all flesh shall see it together.'This is our hope, and this is the faith that I go back to the South with.With this faith, we will be able to hew out of the mountain of despair a stone of hope.With this faith, we will be able to transform the jangling discords of our nation into a beautiful symphony of brotherhood.With this faith, we will be able to work together, to pray together, to struggle together, to go to jail together, to stand up for freedom together, knowing that we will be free one day.And this will be the day-- this will be the day when all of God's children will be able to sing with new meaning:My country 'tis of thee, sweet land of liberty, of thee I sing.Land where my fathers died, land of the Pilgrim's pride,From every mountainside, let freedom ring!And if America is to be a great nation, this must become true.And so let freedom ring from the prodigious hilltops of New Hampshire.Let freedom ring from the mighty mountains of New York.Let freedom ring from the heightening Alleghenies ofPennsylvania.Let freedom ring from the snow - capped Rockies of Colorado.Let freedom ring from the curvaceous slopes of California.But not only that : Let freedom ring from Stone Mountain of Georgia.Let freedom ring from Lookout Mountain of Tennessee.Let freedom ring from every hill and molehill of Mississippi.From every mountainside, let freedom ring.And when this happens, when we allow freedom ring, when we let it ring from every village and every hamlet, from every state and every city, we will be able to speed up that day when all of God's children, black men and white men, Jews and Gentiles, Protestants and Catholics, will be able to join hands and sing in the words of the old Negro spiritual:Free at last!Free at last!Thank God Almighty, we are free at last!\0" };
    int* freq = statistics(I_Have_A_Dream); //根据样本文件，统计各字符的出现频率
    HuffForest* forest = initForest(freq); release(freq); //创建Huffman森林
    HuffTree* tree = generateTree(forest); release(forest); //生成Huffman编码树
    HuffTable* table = generateTable(tree); //将Huffman编码树转换为编码表
    char S[20][20] = { "dream","d","r","e","a","m","i","hellow","world","so","and","this","of","children"};
    for (int i = 0; S[i][0] != '\0'; i++)  //对于命令行传入的每一明文串
    {
        Bitmap* codeString = new Bitmap; //二进制编码串
        int n = encode(table, codeString, S[i]); //将根据编码表生成长度为n的编码串
        decode(tree, codeString, n); //利用Huffman编码树，对长度为n的二进制编码串解码
        printf("\n\n");
        release(codeString);
    }
    release(tree); //释放编码树
    return 0; 
} 