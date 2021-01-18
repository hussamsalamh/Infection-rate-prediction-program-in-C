#include "Person.h"
#define BASE 10
#define ID_LENGTH 9
/**
 * This function allocated the person
 */
Person *PersonAlloc(IdT id, char *name, size_t age, int is_sick) {
    Person *person = (Person *) malloc(sizeof(Person));
    if (person == NULL) {
        return NULL;
    }
    char *save_name = malloc(sizeof(char) * (strlen(name) + 1)); // For saving the name to the memory
    if (save_name == NULL) {
        free(person);
        return NULL;
    }
    strcpy(save_name, name);
    person->name = save_name;
    person->age = age;
    person->id = id;
    person->is_sick = is_sick;
    if (is_sick) {
        person->infection_rate = 1;
    } else {
        person->infection_rate = 0;
    }
    person->meetings_capacity = PERSON_INITIAL_SIZE;
    person->num_of_meetings = 0;
    person->meetings = (Meeting **) malloc(sizeof(Meeting *) * PERSON_INITIAL_SIZE);
    return person;
}

/**
 * This function for free the person
 * @param p_person person
 */
void PersonFree(Person **p_person) {
    if (p_person == NULL || *p_person == NULL) {
        return;
    }
    free((*p_person)->name); // free the name of the person
    (*p_person)->name = NULL;
    free((*p_person)->meetings); // free the meeting of the person
    (*p_person)->meetings = NULL;
    free(*p_person);
    *p_person = NULL;
}


/**
 * This function find out the length of an number
 * @param integer the number
 * @return the length of number
 */
int FindLength(int integer) {
    int len;
    for (len = 1; integer /= BASE; len++);
    return len;
}

/**
 * This function find the meeting by given id
 */
Meeting *PersonGetMeetingById(const Person *const person, IdT id) {
    if (person == NULL || FindLength(id) != ID_LENGTH) {
        return NULL;
    }
    Meeting *meeting;
    for (size_t i = 0; i < person->num_of_meetings; ++i) {
        if (MeetingGetPerson(person->meetings[i], 2)->id == id) {
            meeting = person->meetings[i];
            return meeting;
        }
    }
    return NULL;
}

/**
 * This function add a meeting to the person
 * @param meeting the meeting
 * @param person the person
 * @return pointer to meeting if failed return null
 */
void *AddMeeting(Meeting *meeting, Person *person) {
    if (person == NULL || meeting == NULL) {
        return NULL;
    }
    person->meetings[person->num_of_meetings++] = meeting;
    if (person->num_of_meetings == person->meetings_capacity) {
        person->meetings_capacity *= PERSON_GROWTH_FACTOR;
        person->meetings = realloc(person->meetings, sizeof(Meeting) * person->meetings_capacity);
    }
    return NULL;
}

/**
 The function is used to compare people.
 * @param person_1 (struct Person *) person we would like to compare.
 * @param person_2 (struct Person *) person we would like to compare.
 * @return 0 if the two people are to be considered equal,
 *        -1 if person_1 should be before person_2.
 *         1 if person_1 should be after person_2.
 */
int PersonCompareByName(const Person *person_1, const Person *person_2) {
    int a = strcmp(person_1->name, person_2->name);
    if (a > 0) {
        return 1;
    } else if (a < 0) {
        return -1;
    } else {
        return 0;
    }
}

/**
 The function is used to compare people.
 * @param person_1 (struct Person *) person we would like to compare.
 * @param person_2 (struct Person *) person we would like to compare.
 * @return 0 if the two people are to be considered equal,
 *        -1 if person_1 should be before person_2.
 *         1 if person_1 should be after person_2.
 */
int PersonCompareById(const Person *person_1, const Person *person_2) {
    if (person_1->id < person_2->id) {
        return -1;
    } else if (person_1->id > person_2->id) {
        return 1;
    } else {
        return 0;
    }
}

/**
  The function is used to compare people.
 * @param person_1 (struct Person *) person we would like to compare.
 * @param person_2 (struct Person *) person we would like to compare.
 * @return 0 if the two people are to be considered equal,
 *        -1 if person_1 should be before person_2.
 *         1 if person_1 should be after person_2.
 */
int PersonCompareByInfectionRate(const Person *person_1, const Person *person_2) {
    if (person_1->infection_rate > person_2->infection_rate) {
        return -1;
    } else if (person_2->infection_rate > person_1->infection_rate) {
        return 1;
    } else {
        return 0;
    }
}

/**
 *
 The function is used to compare people.
 * @param person_1 (struct Person *) person we would like to compare.
 * @param person_2 (struct Person *) person we would like to compare.
 * @return 0 if the two people are to be considered equal,
 *        -1 if person_1 should be before person_2.
 *         1 if person_1 should be after person_2.
 */
int PersonCompareByAge(const Person *person_1, const Person *person_2) {
    if (person_1->age > person_2->age) {
        return -1;
    } else if (person_2->age > person_1->age) {
        return 1;
    } else {
        return 0;
    }
}

