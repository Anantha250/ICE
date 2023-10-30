int cNote = 13;
int dNote = 12;
int eNote = 11;
int fNote = 10;
int gNote = 9;
int aNote = 8;
int bNote = 7;
int Piezo = 5;
double c = 261.63;// the frequency of note c
double d = 293.66;// the frequency of note d
double e = 329.63;// the frequency of note e
double f = 349.23;// the frequency of note f
double g = 392;// the frequency of note g
double a = 440;// the frequency of note a
double b = 493.88;// the frequency of note b

const int maxNotes = 100;
int recordedNotes[maxNotes];
int numRecordedNotes = 0;
bool recording = false;

void setup()
{
  pinMode(cNote, INPUT);
  pinMode(dNote, INPUT);
  pinMode(eNote, INPUT);
  pinMode(fNote, INPUT);
  pinMode(gNote, INPUT);
  pinMode(aNote, INPUT);
  pinMode(bNote, INPUT);
  pinMode(Piezo, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(numRecordedNotes);
  if (digitalRead(cNote) == 1) {
    playNote(c);
  } else if (digitalRead(dNote) == 1) {
    playNote(d);
  } else if (digitalRead(eNote) == 1) {
    playNote(e);
  } else if (digitalRead(fNote) == 1) {
    playNote(f);
  } else if (digitalRead(gNote) == 1) {
    playNote(g);
  } else if (digitalRead(aNote) == 1) {
    playNote(a);
  } else if (digitalRead(bNote) == 1) {
    playNote(b);
  }

 
  if (digitalRead(2) == HIGH) {
    recording = !recording; 
    delay(1000); 
  }
    if (digitalRead(4) == HIGH) {
     numRecordedNotes= 0;
  }
  // Recording mode
  if (recording && numRecordedNotes < maxNotes) {
    int noteToRecord = -1;
    if (digitalRead(cNote) == 1) {
      playNote(c);
      noteToRecord = c;
    } else if (digitalRead(dNote) == 1) {
      playNote(d);
      noteToRecord = d;
    } else if (digitalRead(eNote) == 1) {
      playNote(e);
      noteToRecord = e;
    } else if (digitalRead(fNote) == 1) {
      playNote(f);
      noteToRecord = f;
    } else if (digitalRead(gNote) == 1) {
      playNote(g);
      noteToRecord = g;
    } else if (digitalRead(aNote) == 1) {
      playNote(a);
      noteToRecord = a;
    } else if (digitalRead(bNote) == 1) {
      playNote(b);
      noteToRecord = b;
    }

    if (noteToRecord != -1) {
      recordedNotes[numRecordedNotes] = noteToRecord;
      numRecordedNotes++;
      delay(250);
    }
  }

  if (!recording) {
    for (int i = 0; i < numRecordedNotes; i++) {
      playNote(recordedNotes[i]);
      delay(350);
      recording = !recording; 
    }
  }
}

void playNote(double noteFrequency) {
  tone(Piezo, noteFrequency, 250);
}
