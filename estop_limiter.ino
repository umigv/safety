#define wiredPin 2
#define wirelessPin 3
#define limiterPin 4
#define stopPin 5

double pi = 3.1415926535;
double radius = 6.5;
double circ = 2.0*pi*radius;
int curr = 0;
int last = 0;
long tic = 0;
long toc = 0;
long numEdges = 0;
double numRot;
double dist;
long interval = 1000000;//micros
long dt = 0;
double maxSpeed = 5;
double maxDist = maxSpeed*63360/3600*dt;
double maxRot = maxDist/circ;

int wiredSig = LOW;
int wirelessSig = LOW;
int limiterSig = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(wiredPin, INPUT);
  pinMode(wirelessPin, INPUT);
  pinMode(limiterPin, INPUT);
  pinMode(stopPin, OUTPUT);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
}

void loop()
{
  wiredSig = digitalRead(wiredPin);
  wirelessSig = !digitalRead(wirelessPin);
  
  curr = digitalRead(limiterPin);
  if(last==LOW && curr==HIGH)
  {
    numEdges++;
  }
  last = curr;

  toc = micros();
  dt = toc - tic;
  if(dt>=interval)
  {
    numRot = numEdges/360.0;
    dist = circ*numRot;
    maxDist = 5*63360/3600*dt/pow(10,6);
    Serial.println("numEdges: " + String(numEdges));
    Serial.println("numRot: " + String(numRot));
    Serial.println("circ: " + String(circ));
    Serial.println("dist: " + String(dist));
    Serial.println("maxDist: " + String(maxDist));
    Serial.println();
    if(dist>maxDist)
    {
      limiterSig = HIGH;
    }
    else
    {
      limiterSig = LOW;      
    }
        
    numEdges = 0;
    tic = toc;
  }

  if(wiredSig || wirelessSig || limiterSig)
  {
    digitalWrite(stopPin, HIGH);
  }
  else
  {
    digitalWrite(stopPin, LOW);
  }

}
