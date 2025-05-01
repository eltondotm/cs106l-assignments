/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Elton Manchester";

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  std::set<std::string> applicants;
  std::ifstream app_file(filename);
  if (app_file.is_open()) {
    std::string applicant;
    while(getline(app_file, applicant)) {
      applicants.insert(applicant);
    }
  } else {
    std::cerr << "Could not open file: " << filename << std::endl;
  }
  return applicants;
}

/**
 * Takes in a name and returns the initials of that name.
 * Assumes a first and last name with a space between.
 */
std::string initials(std::string name) {
  std::string initials;
  initials += name[0];
  initials += name[name.find(' ') + 1];
  return initials;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*> matches;
  std::string name_initials = initials(name);
  for (auto it = students.begin(); it != students.end(); ++it) {
    if (initials(*it) == name_initials) {
      matches.push(&(*it));
    }
  }
  return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  if (matches.size() == 0) return "NO MATCHES FOUND.";
  int min_diff = INT_MAX;
  std::string closest_match;
  while (!matches.empty()) {
    std::string match = *matches.front();
    matches.pop();
    // Clearly, similarity to my own name is the best metric
    int diff = std::abs(kYourName.compare(match));
    if (diff < min_diff) {
      min_diff = diff;
      closest_match = match;
    }
  }
  return closest_match;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
