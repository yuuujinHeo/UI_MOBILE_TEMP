#include "automata.h"
#include <QDebug>
Automata::Automata(){
	cho = 0;
	jung = 0;
	jong = 0;

	// 0 = 어떤한 문자도 셋팅되지 않았음. 1 = 결정자가 있어서 이전 문자가 확실히 종성이 없을경우.
	end = 0; 
	//////////////////////////////////////////////
	changed = 0;
	unreal = 0;
	tmpString = ""; 
	InString = "";
	outString = "";
	// 초성, 중성, 종성의 순서를 강제로 셋팅한다. (Unicode Standard 4.1의 순서를 따름)
	SettingTable(); 
}

void Automata::InputString(const QString& str){
	InString = str;
	Compare();
}

void Automata::Compare(){
	QChar *a;
	a = new QChar(*InString.unicode());
	
	// 유니코드를 확인해서 초,중,종을 결정한다.
	
	/////////////////////////////////////////////////////////////
	// 초성을 확인한다.
	/////////////////////////////////////////////////////////////

	if((a->unicode() >= 0x3131) && (a->unicode() <= 0x314e)){
		//최초 자음이 들어 올 경우
		if(cho == 0	&& jung == 0 && jong == 0){
			OutStringAsCho(*a);
			//setting 초성이 입력 되었음을 알림
			cho = 1;
			changed = 0;
            jongList.clear();
			//////////////////////////////////
			return;
		}		
		//자음 두개가 연속해서 들어 올 경우 
		if(cho == 1 && jung == 0 && jong ==0){
			OutStringAsCho(*a);
			//setting 초성이 입력 되었음을 알림
			cho = 1;
			changed = 0;
            jongList.clear();
			//////////////////////////////////
			return;
		}
		//초중성이 결정된 상태에서 종성이 들어올경우
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
                //setting 초중종성이 완결됨을 알림
                jong = 1;
            }
			//////////////////////////////////
			return;
		}
		//초중종이 다 결정된 상태에서 초성이 들어올 경우
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
//			//setting 초성이 입력 되었음을 알림
//			cho = 1;
//			jung = 0;
//			jong = 0;
//			changed = 0;
//			//////////////////////////////////
			return;
		}		

	}
	//////////////////////////////////////////////////////////////////////
	// 중성을 확인한다.
	/////////////////////////////////////////////////////////////////////
	if((a->unicode() >= 0x314f) && (a->unicode() <= 0x3163)){
		//최초 중성이 들어 올 경우
		if(cho == 0 && jung == 0 && jong ==0){ 
			outString = *a;
//			tmpString = outString;
			//seeting 문자로서의 입력이 중성으로 끝남
		//	end = 1;
			changed = 0;
			Reset();
			/////////////////////////////////////////
			return; 
		}
		//초성후 중성이 들어 올 경우
		if(cho == 1 && jung == 0 && jong == 0){
			OutStringAsJung(*a);
			//setting 초성과중성이 결합했음을 알림
			jung = 1;
			changed = 1; //상태가 바뀌면서 초성을 지움
			/////////////////////////////////////
			return;
		}
		//이전문자가 종성까지 있고 중성이 들어올 경우
		if(cho == 1 && jung == 1 && jong == 1){
			//이전문자에서 종성값을 확인한다.
            int tmp_i = ((((tmpString.unicode())->unicode()) - 0xAC00) % 28);


            if(jongList.size() == 2){
                tmpString = QChar((((tmpString.unicode())->unicode()) - tmp_i + findjong(jongList[0].unicode())));

                //초성과 중성을 결정하면서 문자를 만든다.
                OutStringAsCho(jongList[1].unicode());
                OutStringAsJung(*a);

            }else{

                QChar tmp_c = QChar(jongsung[tmp_i-1]);

                //종성값을 삭제한 이전 문자를 저장한다.
                tmpString = QChar((((tmpString.unicode())->unicode()) - tmp_i));
                //초성과 중성을 결정하면서 문자를 만든다.
                OutStringAsCho(tmp_c);
                OutStringAsJung(*a);
            }
			////////////////////////////////////////

			//문자를 출력한다.
			outString = tmpString.append(outString);

			//setting 초성과 중성이 들어왔음을 알리고 end모드를 0으로 바꾼다
			cho = 1;
			jung = 1;
			jong = 0;
			//end = 0;
			unreal = 1; // OutString의 첫번째자를 빼야한다.
			changed = 1; //이전 문자를 지우고 종성이 빠진 문자를 삽입한다.
            jongList.clear();
			/////////////////////////////////////////////////////////////////
			return;
		}
		//초성 중성후 중성이 들어올 경우..
		if(cho == 1 && jung == 1 && jong == 0){
			//outString = *a;
			ushort tmp_cho;
			ushort tmp_jung;
			ushort tmp_jung2;


			//중성값을 확인한다.
			tmp_jung = ((((outString.unicode())->unicode())-0xAC00)/28)%21;

			//초성값을 확인한다.
			tmp_cho = ((((outString.unicode()->unicode()))-0xAC00)/28)/21;

			//초성값을 입력한다.
			OutStringAsCho(QChar(chosung[tmp_cho]));

			//중성값을 입력한다.
			//동일 중성값일 경우
			tmp_jung2 = findjung(a->unicode());
			if(tmp_jung == tmp_jung2){
				//OutStringAsJung(QChar(jungsung[tmp_jung]));
				outString = *a;
				tmpString = outString;
				changed = 0;
				Reset();
				return;
			}
			//이중 중성값 합산 및 선택
			//"ㅏㅑㅓㅕㅗㅛㅜㅡ" 7개 중성값만이 선택된 다른 중성값과 결합 가능하다.
			//아래는 헥사코드 버전
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
			//이곳은 테이블 번호를 사용함
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

			
			//다음 코드는 중성 합산으로 이중중성이 표현될수있는 코드에서만 사용하능하다.
			//tmp_jung += findjung(a->unicode())+1; // 중성 합산
			//OutStringAsJung(QChar(jungsung[tmp_jung]));
			///////////////////////////////////////////////////////////////////////////
	//		}
			///////////////////////////////////////////
					 


//			tmpString = outString;
			//seeting 문자로서의 입력이 중성으로 끝남
			//end = 1;
			changed = 1;
//			Reset();
			/////////////////////////////////////////
			return; 
		}
	
	}

	// 한글 유니코드 이외의 문자는 그대로 출력 시켜준다.
	Reset();
	end = 0;
	changed = 0;
	tmpString = ""; 
	outString = "";
	outString = *a;
	///////////////////////////////////////////////////////
			
}

void Automata::OutStringAsCho(QChar cha){
	//문자 두개를 갖을 경우 첫번째 문자를 삭제 한다.
	if(unreal == 1){
		outString.remove(1);
		unreal = 0;
	}
	////////////////////////////////////////////////

	outString = cha;
}

void Automata::OutStringAsJung(QChar cha){
	//문자 두개를 갖을 경우 첫번째 문자를 삭제 한다.
	if(unreal == 1){
		outString.remove(1);
		unreal = 0;
	}
	////////////////////////////////////////////////
    qDebug() << outString << ((findcho((outString.unicode())->unicode())*21)+findjung(cha.unicode()))*28 + 0xAC00 << QChar(((findcho((outString.unicode())->unicode())*21)+findjung(cha.unicode()))*28 + 0xAC00);
	outString = QChar(((findcho((outString.unicode())->unicode())*21)+findjung(cha.unicode()))*28 + 0xAC00);
}

void Automata::OutStringAsDoubleJong(QChar cha){
    //문자 두개를 갖을 경우 첫번째 문자를 삭제 한다.
    if(unreal == 1){
        outString.remove(1);
        unreal = 0;
    }
    outString = QChar((outString.unicode())->unicode() -findjong(jongList[0].unicode()) + findjong(cha.unicode()));
    //tmpString은 항상 이전문자의 값을 갖고 있는다.
    tmpString = outString;
    changed = 1;
}
void Automata::OutStringAsJong(QChar cha){
	//문자 두개를 갖을 경우 첫번째 문자를 삭제 한다.
	if(unreal == 1){
		outString.remove(0,1);
		unreal = 0;
	}
	////////////////////////////////////////////////
//    qDebug() << (outString.unicode())->unicode() << cha.unicode() << findjong(cha.unicode());
	outString = QChar((outString.unicode())->unicode() + findjong(cha.unicode()));
	
	//tmpString은 항상 이전문자의 값을 갖고 있는다.
	tmpString = outString;

//    qDebug() << "JOONG " << cha << outString << tmpString;
	//종성까지 완성 되었으므로 플레그를 다시 셋팅해준다.
	//end = 2;
	changed = 1;
//	Reset();
	//////////////////////////////////////////////////////
}

//구현 차후///////////////////
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
	//초성 초기화
    chosung[0] =  0x3131;    //ㄱ
    chosung[1] =  0x3132;    //ㄲ
    chosung[2] =  0x3134;    //ㄴ
    chosung[3] =  0x3137;    //ㄷ
    chosung[4] =  0x3138;    //ㄸ
    chosung[5] =  0x3139;    //ㄹ
    chosung[6] =  0x3141;    //ㅁ
    chosung[7] =  0x3142;    //ㅂ
    chosung[8] =  0x3143;    //ㅃ
    chosung[9] =  0x3145;    //ㅅ
    chosung[10] = 0x3146;    //ㅆ
    chosung[11] = 0x3147;    //ㅇ
    chosung[12] = 0x3148;    //ㅈ
    chosung[13] = 0x3149;   //ㅉ
    chosung[14] = 0x314A;   //ㅊ
    chosung[15] = 0x314B;   //ㅋ
    chosung[16] = 0x314C;   //ㅌ
    chosung[17] = 0x314D;   //ㅍ
    chosung[18] = 0x314E;   //ㅎ
	//중성 초기화
    jungsung[0] = 0x314f;   //ㅏ
    jungsung[1] = 0x3150;   //ㅐ
    jungsung[2] = 0x3151;   //ㅑ
    jungsung[3] = 0x3152;   //ㅒ
    jungsung[4] = 0x3153;   //ㅓ
    jungsung[5] = 0x3154;   //ㅔ
    jungsung[6] = 0x3155;   //ㅕ
    jungsung[7] = 0x3156;   //ㅖ
    jungsung[8] = 0x3157;   //ㅗ
    jungsung[9] = 0x3158;   //ㅘ
    jungsung[10] = 0x3159;  //ㅙ
    jungsung[11] = 0x315a;  //ㅚ
    jungsung[12] = 0x315b;  //ㅛ
    jungsung[13] = 0x315c;  //ㅜ
    jungsung[14] = 0x315d;  //ㅝ
    jungsung[15] = 0x315e;  //ㅞ
    jungsung[16] = 0x315f;  //ㅟ
    jungsung[17] = 0x3160;  //ㅠ
    jungsung[18] = 0x3161;  //ㅡ
    jungsung[19] = 0x3162;  //ㅢ
    jungsung[20] = 0x3163;  //ㅣ
	//종성 초기화
    jongsung[0] = 0x3131;   //ㄱ
    jongsung[1] = 0x3132;   //ㄲ
    jongsung[2] = 0x3133;   //ㄳ
    jongsung[3] = 0x3134;   //ㄴ
    jongsung[4] = 0x3135;   //ㄵ
    jongsung[5] = 0x3136;   //ㄶ
    jongsung[6] = 0x3137;   //ㄷ
    jongsung[7] = 0x3139;   //ㄹ
    jongsung[8] = 0x313A;   //ㄺ
    jongsung[9] =  0x313B;  //ㄻ
    jongsung[10] = 0x313C;  //ㄼ
    jongsung[11] = 0x313D;  //ㄽ
    jongsung[12] = 0x313E;  //ㄾ
    jongsung[13] = 0x313F;  //ㄿ
    jongsung[14] = 0x3140;  //ㅀ
    jongsung[15] = 0x3141;  //ㅁ
    jongsung[16] = 0x3142;  //ㅂ
    jongsung[17] = 0x3144;  //ㅄ
    jongsung[18] = 0x3145;  //ㅅ
    jongsung[19] = 0x3146;  //ㅆ
    jongsung[20] = 0x3147;  //ㅇ
    jongsung[21] = 0x3148;  //ㅈ
    jongsung[22] = 0x314a;  //ㅊ
    jongsung[23] = 0x314b;  //ㅋ
    jongsung[24] = 0x314c;  //ㅌ
    jongsung[25] = 0x314d;  //ㅍ
    jongsung[26] = 0x314e;  //ㅎ
	jongsung[27] = 0;
}


//초,중,종성 자리 찾기///////////////
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
