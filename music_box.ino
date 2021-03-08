// Include the Stepper library:
#include <Stepper.h>

// ----------------------
// Stepper Motor Settings
// ----------------------

#define STEPS_PER_REVOLUTION 200
#define SP1 8
#define SP2 9
#define SP3 10
#define SP4 11

// --------------
// Music Settings
// --------------

#define BPM 90
#define OCTAVE_SHIFT -3

// ---------------------------
// Musical Scale (do not edit)
// ---------------------------

#define C 16.35
#define Db 17.32
#define D 18.35
#define Eb 19.45
#define E 20.6
#define F 21.83
#define Gb 23.12
#define G 24.5
#define Ab 25.96
#define A 27.5
#define Bb 29.14
#define B 30.87

// -----------------------------
// Music variables (do not edit)
// -----------------------------

#define BEAT_IN_MILLIS 60000.0/BPM
#define STACCATO_DELAY_IN_MILLIS 50

// -----------
// Code Begins
// -----------

// Initialize the stepper library
Stepper musicBox = Stepper(STEPS_PER_REVOLUTION, SP1, SP2, SP3, SP4);

// Play a little startup tune
void setup() {
  note(0.125, C,  0);
  note(0.125, Db, 0);
  note(0.125, D,  0);
  note(0.125, Eb, 0);
  note(0.125, E,  0);
  note(0.125, F,  0);
  note(0.125, Gb, 0);
  note(0.125, G,  0);
  note(0.125, Ab, 0);
  note(0.125, A,  0);
  note(0.125, Bb, 0);
  note(0.125, B,  0);
  note(0.25,  C,  1);
  rest(0.25);
  note(0.5,   C,  0);
  restMillis(1500);
}

// Tabi no Tochuu
void loop() {
  note(0.5,  Bb, 0);
  note(0.5,  C,  1);
  note(0.25, D,  1);
  note(0.25, Eb, 1);
  note(1.5,  D,  1);
  note(0.5,  Bb, 0);
  note(0.5,  C,  1);
  note(0.25, Db, 1);
  note(0.25, Eb, 1);
  note(2.5,  Db, 1);
  note(0.5,  Db, 1);
  note(0.5,  Db, 1);
  note(0.5,  Db, 1);
  note(1.0,  C,  1);
  note(0.5,  A,  0);
  note(2.0,  F,  0);
  rest(4.0);
}

void note(float beats, float note, int octave) {
  // Store the last note, and determine if there should be a short pause so that
  // repeated notes are not lost.
  static float previousNote = 0;
  static int previousOctave = 0;
  bool staccato = (previousNote == note && previousOctave == octave);
  previousNote = note;
  previousOctave = octave;

  // Convert the beats into milliseconds...
  float duration = beats * BEAT_IN_MILLIS;
  // If the note should be staccato, include a small rest...
  if(staccato == true) {
    duration -= STACCATO_DELAY_IN_MILLIS;
  }
  // Convert the note and octave into RPM for the stepper motor
  int speed = (note * pow(2, octave+OCTAVE_SHIFT)) * 60;
  // int steps = (((speed*200)/60)/1000)*duration;
  // simplifies to...
  int steps = (speed/300.0)*duration;

  // If the note should be staccato, include a small rest...
  if(staccato == true) {
    restMillis(STACCATO_DELAY_IN_MILLIS);
  }

  // Play the note...
  musicBox.setSpeed(speed);
  musicBox.step(steps);
}

void rest(float beats) {
  // Convert the beats into milliseconds...
  float duration = beats * BEAT_IN_MILLIS;
  // And rest for that duration...
  restMillis(duration);
}

void restMillis(int millis) {
  // Disable hold position (unwanted noise)...
  disableStepper();
  // Wait for the duration...
  delay(millis);
}

void disableStepper() {
  digitalWrite(SP1, LOW);
  digitalWrite(SP2, LOW);
  digitalWrite(SP3, LOW);
  digitalWrite(SP4, LOW);
}
