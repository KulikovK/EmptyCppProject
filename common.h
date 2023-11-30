#pragma once
#include <iostream>
namespace banana 
{
	namespace common 
	{
		namespace Utils 
		{
			template<class T>
			bool isThisBanana(T banana)
			{
				return banana.AreYouABanana();
			}

			static void PPP(void* ptr);

		}

	}
}