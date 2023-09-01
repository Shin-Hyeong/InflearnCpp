#include <istream>
using namespace std;

//한번 정해지면 절대 바뀌지 않는 값들.
//constant의 약자인 const를 붙임 (변수를 상수화 한다고 함.)
//const을 붙였으면 초기값을 반드시 지정해야 함.

const int AIR = 0;
const int STUN = 1;
const int POLYMORPH =2;
const int INVINCIBLE = 3;
//const를 붙여 수정할 수 없도록 안전성을 높임.

int main()
{
   unsigned char flag;
   // 0b 0000 [무적] [변이] [스턴] [공중부양]

   /*무적 상태로 만든다.*/
   flag = (1 << INVINCIBLE); // flag = 0b1000
   //(1 << 3) 형태는 하드 코딩 형태이다. 나중에 BitFlag가 증가하면 그에 맞게 이동하는 수가 바뀌어야 한다.
   //(1 << INVINCIBLE) 형태로 하여 총괄적으로 관리 가능하도록 만든다.
   //INVINCIBLE는 상수로 메모리에 할당되지 않고 컴파일러가 상수 위치에 3을 대입시킨다. -> 컴파일러마다 다름.

   /*변이 상태를 추가한다 (무적 + 변이)*/
   flag = (1 << POLYMORPH); // flag = 0b1000 + 0b0100 = 0b1100

   // 무적인지 확인하고 싶다(다른 상태는 관심 없음)
   // bitmask를 사용한다. -> 필요한 bit만 추출해서 사용.
   bool invincible = ((flag & (1 << INVINCIBLE) != 0));
   // flag (0b1100) & 1 << 3 (0b0100) = 0b0100 != 0 -> true

   // 무적이거나 스턴상태인지 확인하고 싶다.
   bool mask = (1 << INVINCIBLE) | (1 << STUN); // 0b1010
   bool sturnOrInvincible = ((flag & mask) != 0);
   // flag (0b1100) & mask (0b1010) -> 0b1000 != 0 -> true

   return 0;
}