#pragma once
#include <mutex>
#include <functional>
#include <vector>

static class QuestionManager 
{
private:
	QuestionManager();
	~QuestionManager();
public:
	static void SetupQuestion(std::string question, std::vector<int> questionsInput, int answer);
};