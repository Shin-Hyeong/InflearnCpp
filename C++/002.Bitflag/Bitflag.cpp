#include <istream>
using namespace std;

int main()
{
   unsigned char flag;
   // 0b 0000 [����] [����] [����] [���ߺξ�]

   // ���� ���·� �����.
   flag = (1 << 3); // flag = 0b1000

   // ���� ���¸� �߰��Ѵ� (���� + ����)
   flag = (1 << 2); // flag = 0b1000 + 0b0100 = 0b1100

   // �������� Ȯ���ϰ� �ʹ�(�ٸ� ���´� ���� ����)
   // bitmask�� ����Ѵ�. -> �ʿ��� bit�� �����ؼ� ���.
   bool invincible = ((flag & (1 << 3) != 0));
   // flag (0b1100) & 1 << 3 (0b0100) = 0b0100 != 0 -> true

   // �����̰ų� ���ϻ������� Ȯ���ϰ� �ʹ�.
   bool mask = (1 << 3) | (1 << 1); // 0b1010
   bool sturnOrInvincible = ((flag & mask) != 0);
   // flag (0b1100) & mask (0b1010) -> 0b1000 != 0 -> true

   return 0;
}