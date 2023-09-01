#include <istream>
using namespace std;

//�ѹ� �������� ���� �ٲ��� �ʴ� ����.
//constant�� ������ const�� ���� (������ ���ȭ �Ѵٰ� ��.)
//const�� �ٿ����� �ʱⰪ�� �ݵ�� �����ؾ� ��.

const int AIR = 0;
const int STUN = 1;
const int POLYMORPH =2;
const int INVINCIBLE = 3;
//const�� �ٿ� ������ �� ������ �������� ����.

int main()
{
   unsigned char flag;
   // 0b 0000 [����] [����] [����] [���ߺξ�]

   /*���� ���·� �����.*/
   flag = (1 << INVINCIBLE); // flag = 0b1000
   //(1 << 3) ���´� �ϵ� �ڵ� �����̴�. ���߿� BitFlag�� �����ϸ� �׿� �°� �̵��ϴ� ���� �ٲ��� �Ѵ�.
   //(1 << INVINCIBLE) ���·� �Ͽ� �Ѱ������� ���� �����ϵ��� �����.
   //INVINCIBLE�� ����� �޸𸮿� �Ҵ���� �ʰ� �����Ϸ��� ��� ��ġ�� 3�� ���Խ�Ų��. -> �����Ϸ����� �ٸ�.

   /*���� ���¸� �߰��Ѵ� (���� + ����)*/
   flag = (1 << POLYMORPH); // flag = 0b1000 + 0b0100 = 0b1100

   // �������� Ȯ���ϰ� �ʹ�(�ٸ� ���´� ���� ����)
   // bitmask�� ����Ѵ�. -> �ʿ��� bit�� �����ؼ� ���.
   bool invincible = ((flag & (1 << INVINCIBLE) != 0));
   // flag (0b1100) & 1 << 3 (0b0100) = 0b0100 != 0 -> true

   // �����̰ų� ���ϻ������� Ȯ���ϰ� �ʹ�.
   bool mask = (1 << INVINCIBLE) | (1 << STUN); // 0b1010
   bool sturnOrInvincible = ((flag & mask) != 0);
   // flag (0b1100) & mask (0b1010) -> 0b1000 != 0 -> true

   return 0;
}