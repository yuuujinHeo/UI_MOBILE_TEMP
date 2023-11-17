#include "automata.h"
#include <QDebug>
Automata::Automata(){
	cho = 0;
	jung = 0;
	jong = 0;

	// 0 = ��� ���ڵ� ���õ��� �ʾ���. 1 = �����ڰ� �־ ���� ���ڰ� Ȯ���� ������ �������.
	end = 0; 
	//////////////////////////////////////////////
	changed = 0;
	unreal = 0;
	tmpString = ""; 
	InString = "";
	outString = "";
	// �ʼ�, �߼�, ������ ������ ������ �����Ѵ�. (Unicode Standard 4.1�� ������ ����)
	SettingTable(); 
}

void Automata::InputString(const QString& str){
	InString = str;
	Compare();
}

void Automata::Compare(){
	QChar *a;
	a = new QChar(*InString.unicode());
	
	// �����ڵ带 Ȯ���ؼ� ��,��,���� �����Ѵ�.
	
	/////////////////////////////////////////////////////////////
	// �ʼ��� Ȯ���Ѵ�.
	/////////////////////////////////////////////////////////////

	if((a->unicode() >= 0x3131) && (a->unicode() <= 0x314e)){
		//���� ������ ��� �� ���
		if(cho == 0	&& jung == 0 && jong == 0){
			OutStringAsCho(*a);
			//setting �ʼ��� �Է� �Ǿ����� �˸�
			cho = 1;
			changed = 0;
            jongList.clear();
			//////////////////////////////////
			return;
		}		
		//���� �ΰ��� �����ؼ� ��� �� ��� 
		if(cho == 1 && jung == 0 && jong ==0){
			OutStringAsCho(*a);
			//setting �ʼ��� �Է� �Ǿ����� �˸�
			cho = 1;
			changed = 0;
            jongList.clear();
			//////////////////////////////////
			return;
		}
		//���߼��� ������ ���¿��� ������ ���ð��
		if(cho == 1 && jung == 1 && jong == 0){
            if(findjong(a->unicode()) == 29){
                OutStringAsCho(*a);
                cho = 1;
                jung = 0;
                jong = 0;
                changed = 0;
                jongList.clear();
            }else{
                jongList.push_back(*a);
                OutStringAsJong(*a);
                //setting ���������� �ϰ���� �˸�
                jong = 1;
            }
			//////////////////////////////////
			return;
		}
		//�������� �� ������ ���¿��� �ʼ��� ���� ���
		if(cho == 1 && jung == 1 && jong ==1){
            jongList.push_back(*a);
            qDebug() << jongList.size() << jongList[0];
            if(jongList.size() > 2){
                OutStringAsCho(*a);
                cho = 1;
                jung = 0;
                jong = 0;
                changed = 0;
                jongList.clear();
            }else{
                if(jongList[0] == 0x3131 && jongList[1] == 0x3145){
                    OutStringAsDoubleJong(QChar(0x3133));
                }else if(jongList[0] == 0x3134 && jongList[1] == 0x3148){
                    OutStringAsDoubleJong(QChar(0x3135));
                }else if(jongList[0] == 0x3134 && jongList[1] == 0x314e){
                    OutStringAsDoubleJong(QChar(0x3136));
                }else if(jongList[0] == 0x3139 && jongList[1] == 0x3131){
                    OutStringAsDoubleJong(QChar(0x313A));
                }else if(jongList[0] == 0x3139 && jongList[1] == 0x3141){
                    OutStringAsDoubleJong(QChar(0x313B));
                }else if(jongList[0] == 0x3139 && jongList[1] == 0x3142){
                    OutStringAsDoubleJong(QChar(0x313C));
                }else if(jongList[0] == 0x3139 && jongList[1] == 0x3145){
                    OutStringAsDoubleJong(QChar(0x313D));
                }else if(jongList[0] == 0x3139 && jongList[1] == 0x314c){
                    OutStringAsDoubleJong(QChar(0x313E));
                }else if(jongList[0] == 0x3139 && jongList[1] == 0x314d){
                    OutStringAsDoubleJong(QChar(0x313F));
                }else if(jongList[0] == 0x3139 && jongList[1] == 0x314e){
                    OutStringAsDoubleJong(QChar(0x3140));
                }else if(jongList[0] == 0x3142 && jongList[1] == 0x3145){
                    OutStringAsDoubleJong(QChar(0x3144));
                }else{
                    OutStringAsCho(*a);
                    cho = 1;
                    jung = 0;
                    jong = 0;
                    changed = 0;
                    jongList.clear();
                }
            }


//			OutStringAsCho(*a);
//			//setting �ʼ��� �Է� �Ǿ����� �˸�
//			cho = 1;
//			jung = 0;
//			jong = 0;
//			changed = 0;
//			//////////////////////////////////
			return;
		}		

	}
	//////////////////////////////////////////////////////////////////////
	// �߼��� Ȯ���Ѵ�.
	/////////////////////////////////////////////////////////////////////
	if((a->unicode() >= 0x314f) && (a->unicode() <= 0x3163)){
		//���� �߼��� ��� �� ���
		if(cho == 0 && jung == 0 && jong ==0){ 
			outString = *a;
//			tmpString = outString;
			//seeting ���ڷμ��� �Է��� �߼����� ����
		//	end = 1;
			changed = 0;
			Reset();
			/////////////////////////////////////////
			return; 
		}
		//�ʼ��� �߼��� ��� �� ���
		if(cho == 1 && jung == 0 && jong == 0){
			OutStringAsJung(*a);
			//setting �ʼ����߼��� ���������� �˸�
			jung = 1;
			changed = 1; //���°� �ٲ�鼭 �ʼ��� ����
			/////////////////////////////////////
			return;
		}
		//�������ڰ� �������� �ְ� �߼��� ���� ���
		if(cho == 1 && jung == 1 && jong == 1){
			//�������ڿ��� �������� Ȯ���Ѵ�.
            int tmp_i = ((((tmpString.unicode())->unicode()) - 0xAC00) % 28);


            if(jongList.size() == 2){
                tmpString = QChar((((tmpString.unicode())->unicode()) - tmp_i + findjong(jongList[0].unicode())));

                //�ʼ��� �߼��� �����ϸ鼭 ���ڸ� �����.
                OutStringAsCho(jongList[1].unicode());
                OutStringAsJung(*a);

            }else{

                QChar tmp_c = QChar(jongsung[tmp_i-1]);

                //�������� ������ ���� ���ڸ� �����Ѵ�.
                tmpString = QChar((((tmpString.unicode())->unicode()) - tmp_i));
                //�ʼ��� �߼��� �����ϸ鼭 ���ڸ� �����.
                OutStringAsCho(tmp_c);
                OutStringAsJung(*a);
            }
			////////////////////////////////////////

			//���ڸ� ����Ѵ�.
			outString = tmpString.append(outString);

			//setting �ʼ��� �߼��� �������� �˸��� end��带 0���� �ٲ۴�
			cho = 1;
			jung = 1;
			jong = 0;
			//end = 0;
			unreal = 1; // OutString�� ù��°�ڸ� �����Ѵ�.
			changed = 1; //���� ���ڸ� ����� ������ ���� ���ڸ� �����Ѵ�.
            jongList.clear();
			/////////////////////////////////////////////////////////////////
			return;
		}
		//�ʼ� �߼��� �߼��� ���� ���..
		if(cho == 1 && jung == 1 && jong == 0){
			//outString = *a;
			ushort tmp_cho;
			ushort tmp_jung;
			ushort tmp_jung2;


			//�߼����� Ȯ���Ѵ�.
			tmp_jung = ((((outString.unicode())->unicode())-0xAC00)/28)%21;

			//�ʼ����� Ȯ���Ѵ�.
			tmp_cho = ((((outString.unicode()->unicode()))-0xAC00)/28)/21;

			//�ʼ����� �Է��Ѵ�.
			OutStringAsCho(QChar(chosung[tmp_cho]));

			//�߼����� �Է��Ѵ�.
			//���� �߼����� ���
			tmp_jung2 = findjung(a->unicode());
			if(tmp_jung == tmp_jung2){
				//OutStringAsJung(QChar(jungsung[tmp_jung]));
				outString = *a;
				tmpString = outString;
				changed = 0;
				Reset();
				return;
			}
			//���� �߼��� �ջ� �� ����
			//"�����äŤǤˤ̤�" 7�� �߼������� ���õ� �ٸ� �߼����� ���� �����ϴ�.
			//�Ʒ��� ����ڵ� ����
			/*
			else if(tmp_jung == 0x314f || tmp_jung == 0x3151 || tmp_jung == 0x3153 || tmp_jung == 0x3155 ||tmp_jung == 0x3157||tmp_jung == 0x315c || tmp_jung == 0x3161)
			{
				if(tmp_jung == 0x314f){
					if(tmp_jung2 == 0x3163){
						OutStringAsJung(QChar(0x3150));
					}
					else{
					outString = *a;
					tmpString = outString;
					changed = 0;
					Reset();
					return;
					}				
				}
				else if(tmp_jung == 0x3153){
					if(tmp_jung2 == 0x3163){
						OutStringAsJung(QChar(0x3152));
					}
					else{
					outString = *a;
					tmpString = outString;
					changed = 0;
					Reset();
					return;
					}	
				
				}
				else if(tmp_jung == 0x3155){
					if(tmp_jung2 == 0x3156){
						OutStringAsJung(QChar(0x3150));
					}
					else{
					outString = *a;
					tmpString = outString;
					changed = 0;
					Reset();
					return;
					}	
				
				}
				else if(tmp_jung == 0x3157){
					if(tmp_jung2 == 0x314f){
						OutStringAsJung(QChar(0x3158));
					}
					else if(tmp_jung2 == 0x3163){
						OutStringAsJung(QChar(0x315a));
					}
					else{
					outString = *a;
					tmpString = outString;
					changed = 0;
					Reset();
					return;
					}	
				
				}
				else if(tmp_jung == 0x315c){
					if(tmp_jung2 == 0x3153){
						OutStringAsJung(QChar(0x315d));
					}
					else if(tmp_jung2 == 0x3154){
						OutStringAsJung(QChar(0x315e));
					}
					else if(tmp_jung2 == 0x3163){
						OutStringAsJung(QChar(0x315f));
					}
					else{
					outString = *a;
					tmpString = outString;
					changed = 0;
					Reset();
					return;
					}		
				}
				else if(tmp_jung == 0x3161){
					if(tmp_jung2 == 0x3163){
						OutStringAsJung(QChar(0x3162));
					}
					else{
					outString = *a;
					tmpString = outString;
					changed = 0;
					Reset();
					return;
					}
					
				}
			*/////////////////////////////////////////////////////////////////////////////////
			//�̰��� ���̺� ��ȣ�� �����
			else if(tmp_jung == 0 || tmp_jung == 2 || tmp_jung == 4 || tmp_jung == 6 ||tmp_jung == 8||tmp_jung == 13 || tmp_jung == 18)
			{
				if(tmp_jung == 0){
					if(tmp_jung2 == 20){
						OutStringAsJung(QChar(0x3150));
					}
					else{
					outString = *a;
					tmpString = outString;
					changed = 0;
					Reset();
					return;
					}				
				}
				else if(tmp_jung == 2){
					if(tmp_jung2 == 20){
						OutStringAsJung(QChar(0x3152));
					}
					else{
					outString = *a;
					tmpString = outString;
					changed = 0;
					Reset();
					return;
					}	
				
				}
				else if(tmp_jung == 4){
					if(tmp_jung2 == 20){
						OutStringAsJung(QChar(0x3154));
					}
					else{
					outString = *a;
					tmpString = outString;
					changed = 0;
					Reset();
					return;
					}	
				
				}
				else if(tmp_jung == 6){
					if(tmp_jung2 == 20){
						OutStringAsJung(QChar(0x3156));
					}
					else{
					outString = *a;
					tmpString = outString;
					changed = 0;
					Reset();
					return;
					}	
				
				}
				else if(tmp_jung == 8){
					if(tmp_jung2 == 0){
						OutStringAsJung(QChar(0x3158));
					}
					else if(tmp_jung2 == 20){
						OutStringAsJung(QChar(0x315a));
					}
					else{
					outString = *a;
					tmpString = outString;
					changed = 0;
					Reset();
					return;
					}	
				
				}
				else if(tmp_jung == 13){
					if(tmp_jung2 == 4){
						OutStringAsJung(QChar(0x315d));
					}
					else if(tmp_jung2 == 5){
						OutStringAsJung(QChar(0x315e));
					}
					else if(tmp_jung2 == 20){
						OutStringAsJung(QChar(0x315f));
					}
					else{
					outString = *a;
					tmpString = outString;
					changed = 0;
					Reset();
					return;
					}		
				}
				else if(tmp_jung == 18){
					if(tmp_jung2 == 20){
						OutStringAsJung(QChar(0x3162));
					}
					else{
					outString = *a;
					tmpString = outString;
					changed = 0;
					Reset();
					return;
					}
					
				}
			} else {

				outString = *a;
				tmpString = outString;
				changed = 0;
				Reset();
				return;
			}			

			
			//���� �ڵ�� �߼� �ջ����� �����߼��� ǥ���ɼ��ִ� �ڵ忡���� ����ϴ��ϴ�.
			//tmp_jung += findjung(a->unicode())+1; // �߼� �ջ�
			//OutStringAsJung(QChar(jungsung[tmp_jung]));
			///////////////////////////////////////////////////////////////////////////
	//		}
			///////////////////////////////////////////
					 


//			tmpString = outString;
			//seeting ���ڷμ��� �Է��� �߼����� ����
			//end = 1;
			changed = 1;
//			Reset();
			/////////////////////////////////////////
			return; 
		}
	
	}

	// �ѱ� �����ڵ� �̿��� ���ڴ� �״�� ��� �����ش�.
	Reset();
	end = 0;
	changed = 0;
	tmpString = ""; 
	outString = "";
	outString = *a;
	///////////////////////////////////////////////////////
			
}

void Automata::OutStringAsCho(QChar cha){
	//���� �ΰ��� ���� ��� ù��° ���ڸ� ���� �Ѵ�.
	if(unreal == 1){
		outString.remove(1);
		unreal = 0;
	}
	////////////////////////////////////////////////

	outString = cha;
}

void Automata::OutStringAsJung(QChar cha){
	//���� �ΰ��� ���� ��� ù��° ���ڸ� ���� �Ѵ�.
	if(unreal == 1){
		outString.remove(1);
		unreal = 0;
	}
	////////////////////////////////////////////////
    qDebug() << outString << ((findcho((outString.unicode())->unicode())*21)+findjung(cha.unicode()))*28 + 0xAC00 << QChar(((findcho((outString.unicode())->unicode())*21)+findjung(cha.unicode()))*28 + 0xAC00);
	outString = QChar(((findcho((outString.unicode())->unicode())*21)+findjung(cha.unicode()))*28 + 0xAC00);
}

void Automata::OutStringAsDoubleJong(QChar cha){
    //���� �ΰ��� ���� ��� ù��° ���ڸ� ���� �Ѵ�.
    if(unreal == 1){
        outString.remove(1);
        unreal = 0;
    }
    outString = QChar((outString.unicode())->unicode() -findjong(jongList[0].unicode()) + findjong(cha.unicode()));
    //tmpString�� �׻� ���������� ���� ���� �ִ´�.
    tmpString = outString;
    changed = 1;
}
void Automata::OutStringAsJong(QChar cha){
	//���� �ΰ��� ���� ��� ù��° ���ڸ� ���� �Ѵ�.
	if(unreal == 1){
		outString.remove(0,1);
		unreal = 0;
	}
	////////////////////////////////////////////////
//    qDebug() << (outString.unicode())->unicode() << cha.unicode() << findjong(cha.unicode());
	outString = QChar((outString.unicode())->unicode() + findjong(cha.unicode()));
	
	//tmpString�� �׻� ���������� ���� ���� �ִ´�.
	tmpString = outString;

//    qDebug() << "JOONG " << cha << outString << tmpString;
	//�������� �ϼ� �Ǿ����Ƿ� �÷��׸� �ٽ� �������ش�.
	//end = 2;
	changed = 1;
//	Reset();
	//////////////////////////////////////////////////////
}

//���� ����///////////////////
void Automata::ExJungJong(){


}
/////////////////////////////

void Automata::Reset(){
	cho = 0;
	jung = 0;
	jong = 0;
//	end = 0;
//	changed = 0;
//	tmpString = ""; 
	InString = "";
//	outString = "";

}

void Automata::SettingTable()
{
	//�ʼ� �ʱ�ȭ
    chosung[0] =  0x3131;    //��
    chosung[1] =  0x3132;    //��
    chosung[2] =  0x3134;    //��
    chosung[3] =  0x3137;    //��
    chosung[4] =  0x3138;    //��
    chosung[5] =  0x3139;    //��
    chosung[6] =  0x3141;    //��
    chosung[7] =  0x3142;    //��
    chosung[8] =  0x3143;    //��
    chosung[9] =  0x3145;    //��
    chosung[10] = 0x3146;    //��
    chosung[11] = 0x3147;    //��
    chosung[12] = 0x3148;    //��
    chosung[13] = 0x3149;   //��
    chosung[14] = 0x314A;   //��
    chosung[15] = 0x314B;   //��
    chosung[16] = 0x314C;   //��
    chosung[17] = 0x314D;   //��
    chosung[18] = 0x314E;   //��
	//�߼� �ʱ�ȭ
    jungsung[0] = 0x314f;   //��
    jungsung[1] = 0x3150;   //��
    jungsung[2] = 0x3151;   //��
    jungsung[3] = 0x3152;   //��
    jungsung[4] = 0x3153;   //��
    jungsung[5] = 0x3154;   //��
    jungsung[6] = 0x3155;   //��
    jungsung[7] = 0x3156;   //��
    jungsung[8] = 0x3157;   //��
    jungsung[9] = 0x3158;   //��
    jungsung[10] = 0x3159;  //��
    jungsung[11] = 0x315a;  //��
    jungsung[12] = 0x315b;  //��
    jungsung[13] = 0x315c;  //��
    jungsung[14] = 0x315d;  //��
    jungsung[15] = 0x315e;  //��
    jungsung[16] = 0x315f;  //��
    jungsung[17] = 0x3160;  //��
    jungsung[18] = 0x3161;  //��
    jungsung[19] = 0x3162;  //��
    jungsung[20] = 0x3163;  //��
	//���� �ʱ�ȭ
    jongsung[0] = 0x3131;   //��
    jongsung[1] = 0x3132;   //��
    jongsung[2] = 0x3133;   //��
    jongsung[3] = 0x3134;   //��
    jongsung[4] = 0x3135;   //��
    jongsung[5] = 0x3136;   //��
    jongsung[6] = 0x3137;   //��
    jongsung[7] = 0x3139;   //��
    jongsung[8] = 0x313A;   //��
    jongsung[9] =  0x313B;  //��
    jongsung[10] = 0x313C;  //��
    jongsung[11] = 0x313D;  //��
    jongsung[12] = 0x313E;  //��
    jongsung[13] = 0x313F;  //��
    jongsung[14] = 0x3140;  //��
    jongsung[15] = 0x3141;  //��
    jongsung[16] = 0x3142;  //��
    jongsung[17] = 0x3144;  //��
    jongsung[18] = 0x3145;  //��
    jongsung[19] = 0x3146;  //��
    jongsung[20] = 0x3147;  //��
    jongsung[21] = 0x3148;  //��
    jongsung[22] = 0x314a;  //��
    jongsung[23] = 0x314b;  //��
    jongsung[24] = 0x314c;  //��
    jongsung[25] = 0x314d;  //��
    jongsung[26] = 0x314e;  //��
	jongsung[27] = 0;
}


//��,��,���� �ڸ� ã��///////////////
ushort Automata::findcho(ushort arg)
{
	int i;
	for(i = 0; i < 18; i++){
		if(arg == chosung[i]) break;
	}
	return i;
}

ushort Automata::findjung(ushort arg)
{
	int i;
	for(i = 0; i < 21; i++){
		if(arg == jungsung[i]) break;
	}
	return i;

}

ushort Automata::findjong(ushort arg)
{
	int i;
	for(i = 0; i < 28; i++){
		if(arg == jongsung[i]) break;
	}
	return i+1;
}
/////////////////////////////////////////
