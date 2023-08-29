 #include <istream>
 using namespace std;

 int main(){
    unsigned char flag;
    //0b 0000 [무적] [변이] [스턴] [공중부양]

    //무적 상태로 만든다.
    flag = (1 << 3); // flag = 0b1000

    //변이 상태를 추가한다 (무적 + 변이)
    flag = (1 << 2); // flag = 0b1000 + 0b0100 = 0b1100

    //무적인지 확인하고 싶다(다른 상태는 관심 없음)
    //bitmask를 사용한다. -> 필요한 bit만 추출해서 사용.
    bool invincible = ((flag & (1 << 3) != 0));
    //flag (0b1100) & 1 << 3 (0b0100) = 0b0100 != 0 -> true
    
    //무적이거나 스턴상태인지 확인하고 싶다.
    bool mask = (1 << 3) | (1 << 1); // 0b1010
    bool sturnOrInvincible = ((flag & mask) != 0);
    //flag (0b1100) & mask (0b1010) -> 0b1000 != 0 -> true

    return 0;
 }