/*
 Name:		MCBTF_forGIPI.ino
 Created:	2018/08/07 18:13:43
 Author:	Tetsu Otter
*/
/*
���̃X�P�b�`�́A�ړ_�̊J��ǂ��GIPI�ɏ��𑗐M���邽�߂̂��̂ł��B
�ϒ�R��p���Ĉʒu�����o����^�C�v�̂��͕̂ʂɂ���܂��B
���̂����{�^������⃏���n���h���ɂ��Ή��ł���悤�ɂ��܂��B
*/
#define H HIGH
#define L LOW
const int PPinNum = 5;//�}�X�R��(�͍s�n���h��)�̎g�p����s���̌�
const int MaxP = 2;//�͍s�i��
const int PPin[PPinNum] = { 2,3,4,5,6 };//�}�X�R��(�͍s�n���h��)�̎g�p����s���̔ԍ�
const bool PHL[MaxP + 1][PPinNum] = 
{//�ォ��"P0�̂Ƃ��̐ړ_���", "P1�̂Ƃ��̐ړ_���",,,���A���J�b�R���ɃJ���}��؂��PPin�ɓ��͂������ɓ����B�ړ_���ڐG���Ă����H�A����Ă����L�ƂȂ�B
{H,H,H,H,H},//���J�b�R�̂��Ƃ́u,�v��Y��Ȃ��悤�ɁB
{L,L,L,L,L}
};//�}�X�R���̐ړ_�ƒi���̊֌W

const int BPinNum = 5;//�u���[�L(�����n���h��)�̎g�p����s���̌�
const int MaxB = 2;//�����i��
const int BPin[BPinNum] = { 7,8,9,10,11 };//�u���[�L(�����n���h��)�̎g�p����s���̔ԍ�
const int BHL[MaxB + 1][BPinNum] =
{//�ォ��"B0�̂Ƃ��̐ړ_���", "B1�̂Ƃ��̐ړ_���",,,���A���J�b�R���ɃJ���}��؂��BPin�ɓ��͂������ɓ����B�ړ_���ڐG���Ă����H�A����Ă����L�ƂȂ�B
{ H,H,H,H,H },//���J�b�R�̂��Ƃ́u,�v��Y��Ȃ��悤�ɁB
{ L,L,L,L,L }
};//�u���[�L�̐ړ_�ƒi���̊֌W

const int RPinNum = 2;//���o�[�T�[(�t�]�n���h��)�̎g�p����s���̌�
const int RPin[RPinNum] = { 12,13 };//���o�[�T�[(�t�]�n���h��)�̎g�p����s���̔ԍ�
const int RHL[3][RPinNum] =
{//�ړ_���ڐG���Ă����H�A����Ă����L�ƂȂ�B
{ H,H },//���o�[�T�[�u�O�v�ʒu�̎��̃s�����
{ L,L },//�u���v�ʒu�̎��̃s�����
{ H,L }//�u��v�ʒu�̎��̃s�����
};//���o�[�T�[�̐ړ_�ƈʒu�̊֌W


void setup() {
	Serial.begin(9600);
	while (!Serial);
	Serial.print("TOB" + String(MaxB) + "\r");
	Serial.print("TOP0\r");
	Serial.print("TORN\r");
}

int OldPi = 0;
int OldBi = MaxB;
int OldRi = 1;
void loop() {
	bool PCompTF = false;
	bool BCompTF = false;
	bool RCompTF = false;
	for (int i = 0; i < max(MaxB, MaxP); i++) {
		if (i < MaxP && PCompTF == false) {
			for (int pdr = 0; pdr < PPinNum; pdr++) {
				if (digitalRead(PPin[pdr]) != PHL[i][pdr]) {
					goto Pout;
				}
			}
			//P�i���ui�v�Ɣ��f���ꂽ�B
			if (i != OldPi) {
				Serial.print("TOP" + String(i) + "\r");
				OldPi = i;
			}
			PCompTF = true;
		Pout:;
		}
		if (i < MaxB && BCompTF == false) {
			for (int bdr = 0; bdr < BPinNum; bdr++) {
				if (digitalRead(BPin[bdr]) != BHL[i][bdr]) {
					goto Bout;
				}
			}
			//B�i���ui�v�Ɣ��f���ꂽ�B
			if (i != OldBi) {
				Serial.print("TOB" + String(i) + "\r");
				OldBi = i;
			}
			BCompTF = true;
		Bout:;
		}
		if (i < 3 && RCompTF == false) {
			for (int bdr = 0; bdr < BPinNum; bdr++) {
				if (digitalRead(BPin[bdr]) != BHL[i][bdr]) {
					goto Rout;
				}
			}
			//R�ʒu�ui�v�Ɣ��f���ꂽ�B
			if (OldRi != i) {
				switch (i)
				{
				case 0:
					Serial.print("TORF\r");
					break;
				case 1:
					Serial.print("TORN\r");
					break;
				case 2:
					Serial.print("TORB\r");
					break;
				}
				OldRi = i;
			}
			BCompTF = true;
		Rout:;
		}
		delay(2);
	}
	delay(5);
}
