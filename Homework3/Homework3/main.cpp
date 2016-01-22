#include <iostream>
#include <cstdlib>

class Weight {
private:
	int pounds;
	int ounces;
public:
	Weight(int p, int o) :pounds(p), ounces(o) {}
	Weight() { this->pounds = 0, this->ounces = 0; }
	int getPounds() const {
		return this->pounds;
	}
	int getOunces() const {
		return this->ounces;
	}
	void setPounds(int p) {
		this->pounds = p;
	}
	void setOunces(int o) {
		this->ounces = o % 16;
		this->pounds += o / 16;
	}
	void printWeight() const {
		std::cout << "Weight: " << this->getWeight() << " pounds" << std::endl;
	} const
	double getWeight() const {
		double p = static_cast<double>(this->pounds);
		double o = static_cast<double>(this->ounces);
		return p + (o / 16.0);
	}

	const Weight operator+(const Weight& a) {
		return Weight(this->getPounds() + a.getPounds(), this->getOunces() + a.getOunces());
	}

	const Weight operator-(const Weight& a) {
		return Weight(this->getPounds() - a.getPounds(), this->getOunces() - a.getOunces());
	}

	bool operator==(const Weight& a) {
		return this->getWeight() == a.getWeight();
	}
};

inline void printDetails(Weight obj) {
	std::cout << "Weight: " << obj.getWeight() << " = " << obj.getPounds() << "lb " << obj.getOunces() << "oz" << std::endl;
}

int main() {
	Weight jug(3, 4),book(2, 7),shirt(0, 3),bag(0, 3),air;
	
	
	//What we have
	std::cout << "Objects:" << "\n\tJug ";
	printDetails(jug);
	std::cout << "\n\tBook ";
	printDetails(book);
	std::cout << "\n\tShirt ";
	printDetails(shirt);
	std::cout << "\n\tBag ";
	printDetails(bag);
	std::cout << "\n\tAir ";
	printDetails(air);
	std::cout << std::endl;
	std::cout << std::endl;
	//Test 1: Add
	std::cout << "Weight of Air + Bag " << std::endl;
	printDetails(air + bag);
	std::cout << std::endl;
	std::cout << "Weight of Book + Bag " << std::endl;
	printDetails(book + bag);
	std::cout << std::endl;
	std::cout << "Weight of Jug + Shirt " << std::endl;
	printDetails(jug + shirt);
	std::cout << std::endl;
	//Test 2: Subtract
	std::cout << "Weight of Jug - Book " << std::endl;
	printDetails(jug - book);
	std::cout << std::endl;
	std::cout << "Weight of Shirt - Bag " << std::endl;
	printDetails(shirt-bag);
	std::cout << std::endl;
	std::cout << "Wieght of Book - Jug " << std::endl;
	printDetails(book - jug);
	std::cout << std::endl;
	//Test 3: Equals
	std::cout << "Does the shirt and bag have the same weight? " << (shirt == bag ? "Yep" : "Nope") << std::endl;
	std::cout << std::endl;
	//Test 4: Changing values
	std::cout << "Lets put the books in the bag" << std::endl;
	Weight item = book + bag;
	bag.setOunces(item.getOunces());
	bag.setPounds(item.getPounds());
	bag.printWeight();
	
	std::cout << "Lets put the shirt in the bag" << std::endl;
	Weight item2 = shirt + bag;
	bag.setOunces(item2.getOunces());
	bag.setPounds(item2.getPounds());
	bag.printWeight();
	std::cout << std::endl;
	//Test 5: Detailed Output
	std::cout << "Lets see the weight breakdown of the bag" << std::endl;
	std::cout << "Pounds: " << bag.getPounds() << std::endl;
	std::cout << "Ounces: " << bag.getOunces() << std::endl;
	std::cout << std::endl;
	//Test 6: Another detailed output
	std::cout << "Lets add 24 ounces of water into the jug" << std::endl;
	jug.setOunces(jug.getOunces() + 24);
	jug.printWeight();
	std::cout << "Pounds: " << jug.getPounds() << std::endl;
	std::cout << "Ounces: " << jug.getOunces() << std::endl;
	std::cout << std::endl;
	//Test 7: Weight compare
	std::cout << "Does the jug and bag have the same weight? " << (jug == bag ? "Yep" : "Nope") << std::endl;




}