#include "pch.h"
#include "CppUnitTest.h"
#include "../lab12_11_2/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            TelephoneDirectory directory;
            directory.root = nullptr;
            insertSubscriber(directory.root, "John Doe", "1234567890");
            insertSubscriber(directory.root, "Jane Smith", "9876543210");
            insertSubscriber(directory.root, "Alice Johnson", "5555555555");

            bool found = searchSubscriber(directory.root, "1234567890");
            Assert::AreEqual(found, true);
            
           
        }
	};
}
