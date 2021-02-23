#include <iostream>
#include <array>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode *head = nullptr, *tail = nullptr;
		int carry = 0,sum=0;
		while (l1 && l2) {
			int sum = l1->val + l2->val + carry;
			if (!head) {
				head = tail = new ListNode(sum % 10);
			} else {
				tail->next = new ListNode(sum % 10);
				tail = tail->next;
			}
			carry = sum / 10;
			l1 = l1->next;
			l2 = l2->next;
		}
		if (carry > 0) {
			tail->next = new ListNode(carry);
		}
		return head;
	}
};


int main(){
	ListNode A(1);
	ListNode B(2,&A);
	cout<<(B.next)->val<<endl;
	return 1;
}