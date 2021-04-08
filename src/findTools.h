#if !defined(MatrixGL_findTools_H)
#define MatrixGL_findTools_H 1

const bool * findChar(char c){
  switch(c){
    case '0':
      return f0;
      break;
    case '1':
      return f1;
      break;
    case '2':
      return f2;
      break;
    case '3':
      return f3;
      break;
    case '4':
      return f4;
      break;
    case '5':
      return f5;
      break;
    case '6':
      return f6;
      break;
    case '7':
      return f7;
      break;
    case '8':
      return f8;
      break;
    case '9':
      return f9;
      break;

    case ':':
      return fCol;
      break;
    case ' ':
      return fBLANK;
      break;

    case 'A':
      return fA;
      break;
    case 'B':
      return fB;
      break;
    case 'C':
      return fC;
      break;
    case 'D':
      return fD;
      break;
    case 'E':
      return fE;
      break;
    case 'F':
      return fF;
      break;
    case 'G':
      return fG;
      break;
    case 'H':
      return fH;
      break;
    case 'I':
      return fI;
      break;
    case 'J':
      return fJ;
      break;
    case 'K':
      return fK;
      break;
    case 'L':
      return fL;
      break;
    case 'M':
      return fM;
      break;
    case 'N':
      return fN;
      break;
    case 'O':
      return fO;
      break;
    case 'P':
      return fP;
      break;
    case 'Q':
      return fQ;
      break;
    case 'R':
      return fR;
      break;
    case 'S':
      return fS;
      break;
    case 'T':
      return fT;
      break;
    case 'U':
      return fU;
      break;
    case 'V':
      return fV;
      break;
    case 'W':
      return fW;
      break;
    case 'X':
      return fX;
      break;
    case 'Y':
      return fY;
      break;
    case 'Z':
      return fZ;
      break;

    default:
      return fNULL;
      break;
  }
}

const bool * findNum(int n){
  // Abstraction of `findChar()` that allows an int as an argument
  if(n>9){
    n=0;
  }
  char nS [] = {'0','1','2','3','4','5','6','7','8','9'}; 
  return findChar(nS[n]);
}

#endif