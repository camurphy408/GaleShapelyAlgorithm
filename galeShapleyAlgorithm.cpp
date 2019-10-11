#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// Randomizing the preference list of each man and woman
void randomize(int * arr) {
  for (int i = 0; i < 30; i++) {
    int r = rand() % 30;
    int temp = arr[r];
    arr[r] = arr[i];
    arr[i] = temp;
  }
}

class Person {
public:
  bool free;
  int fate, choiceNum;
  int preferences[30];
  Person() {
    free = true;
    fate = -1;
    choiceNum = -1;
    for (int i = 0; i < 30; i++) {
      preferences[i] = i;
    }
    randomize(preferences);
  }
};

// Finding the first free man in an array of men
int freeMan(Person * men) {
  for (int i = 0; i < 30; i++)
    if (men[i].free)
      return i;
  return -1;
}

// Figuring out how high "fate" is on "peep's" preference list
int choiceNum(Person peep, int fate) {
  for (int i = 0; i < 30; i++)
    if (peep.preferences[i] == fate)
      return i;
  return -1;
}

int main() {

  Person men[30], women[30];
  for (int i = 0; i < 30; i++) {
    men[i] = Person();
    women[i] = Person();
  }

  int firstFreeManIndex = freeMan(men);
  while (firstFreeManIndex != -1) { // while there's a free man
    int choice = 0;
    while (men[firstFreeManIndex].free) { // while this man remains free
      int womanIndex = men[firstFreeManIndex].preferences[choice];
      if (women[womanIndex].free) { // if this woman is free, the couple gets engaged
        men[firstFreeManIndex].fate = womanIndex;
        men[firstFreeManIndex].free = false;
        men[firstFreeManIndex].choiceNum = choice;
        women[womanIndex].fate = firstFreeManIndex;
        women[womanIndex].free = false;
        women[womanIndex].choiceNum = choiceNum(women[womanIndex], firstFreeManIndex);
      }
      else if (women[womanIndex].choiceNum > choiceNum(women[womanIndex], firstFreeManIndex)) { // if this woman likes the current man more than her fiancee, the woman breaks off her engagement and couples up with the new man
        men[women[womanIndex].fate].free = true;
        men[firstFreeManIndex].fate = womanIndex;
        men[firstFreeManIndex].free = false;
        men[firstFreeManIndex].choiceNum = choice;
        women[womanIndex].fate = firstFreeManIndex;
        women[womanIndex].choiceNum = choiceNum(women[womanIndex], firstFreeManIndex);
      }
      else // the man settles on the next woman down on his preference list until he finds a match
        choice++;
    }
    firstFreeManIndex = freeMan(men); // increments to the next free man
  }

  cout << "Each man's fate, and ranking of his fate: " << endl;
  for (int i = 0; i < 30; i++) {
    cout << i << ": " << men[i].fate << ", " << ++men[i].choiceNum << endl;
  }
  cout << "Each woman's fate, and ranking of her fate: " << endl;
  for (int i = 0; i < 30; i++) {
    cout << i << ": " << women[i].fate << ", " << ++women[i].choiceNum << endl;
  }

  double menAve = 0, womenAve = 0;
  for (int i = 0; i < 30; i++) {
    menAve += men[i].choiceNum;
    womenAve += women[i].choiceNum;
  }
  menAve /= 30;
  womenAve /= 30;
  cout<< "Men's average choice number: " << menAve << endl;
  cout << "Women's average choice number: " << womenAve << endl;
  return 0;
}
