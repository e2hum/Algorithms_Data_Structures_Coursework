// Practice Exercise 1

#include <iostream>
#include <vector>
using namespace std;

class Artwork
{
    private:
    string artist, title;
    unsigned int year;
    
    public:
    // default constructor
    Artwork() : year(0) {}

    // parametric constructor
    Artwork(string new_artist, string new_title, unsigned int new_year) : 
    artist(new_artist), title(new_title), year(new_year) {}

    string get_artist()
    {
        return artist;
    }

    string get_title()
    {
        return title;
    }

    unsigned int get_year()
    {
        return year;
    }

    bool operator==(const Artwork & target) const
    {
        //fragmented for readability
        bool are_equal = artist == target.artist;
        are_equal = are_equal && title == target.title;
        are_equal = are_equal && year == target.year;
        return are_equal;
    }
    void print(){
    	cout << "Artist: " << artist << endl << "Title: " << title << endl
        << "Year: " << year << endl;
	}
};

class SoldArtwork : public Artwork
{
    private:
    string customer_name, customer_address;
    double sale_amount;

    public:
    // default constructor
    SoldArtwork() : sale_amount(0) {}

    // Parametric constructor
    SoldArtwork(Artwork old, string new_name, string new_address, double new_amount) :
    Artwork(old), customer_name(new_name), customer_address(new_address), sale_amount(new_amount) {}

    bool operator==(const SoldArtwork & target) const
    {
        // checks to make sure the Artwork is the same before checking the buyer information
        bool are_equal = Artwork::operator==(target) && customer_name == target.customer_name;
        are_equal = are_equal && customer_address == target.customer_address;
        are_equal = are_equal && sale_amount == target.sale_amount;
        return are_equal;
    }

    void print(){
		Artwork::print();
		cout << "Buyer Name: "<< customer_name << endl <<"Buyer Address: "<< customer_address << endl
        <<"Sale Amount: "<< sale_amount << endl;
	}
};

class ArtCollection 
{
    vector <Artwork> have;
    vector <SoldArtwork> sold;

    public:
    // Size of both Artwork and SoldArtwork vectors
    int size() 
    {
    	cout<< "have: " <<have.size() <<"  sold: "<<sold.size()<<endl;
        return have.size() + sold.size();
    }

    bool insert_artwork(const Artwork& other){
        bool dupe = false;
        for(vector<Artwork>::iterator my_it=have.begin();my_it!=have.end();my_it++){
            if (other == *my_it){
                dupe = true;
                cout << "Duplicate found. Artwork not added." << endl;
            }
		}
        if (!dupe){
            have.push_back(other);
            return true;
        }
		else{
            return false;
        }
    }

    bool sell_artwork(const SoldArtwork& other){
        static_cast<Artwork>(other);
        for (int index = 0; index < have.size(); index++){
            if (have[index] == other){
                sold.push_back(other);
                have.erase(have.begin()+index);
                index--;
                return true;
            }
        }
        cout << "Artwork not found. Cannot sell." << endl;
        return false;
    }
	
    bool operator==(const ArtCollection& other) const
    {
        int count = 0;
        if (have.size() != other.have.size() ||
			 sold.size() != other.sold.size()){
			return false;
			}
	        
        for(int art1 = 0; art1 < have.size(); art1++){
            for (int art2 = 0; art2 < have.size(); art2++){
                if (have[art1] == other.have[art2])
                    count++;                    
            }           
        }
        if (count == have.size()){
            //check operator
            count = 0;
            for(int art1 = 0; art1 < sold.size(); art1++){
                for (int art2 = 0; art2 < sold.size(); art2++){
                    if (sold[art1] == other.sold[art2])
                    count++;
                }
            }
            if (count == sold.size())
                return true;
        }
        return false;
	}

    friend ArtCollection operator+(ArtCollection& original, ArtCollection& other);
    friend class ArtCollectionTest;
};	


ArtCollection operator+(ArtCollection& original, ArtCollection& other) 
{
    ArtCollection temp;
    temp.have.insert(temp.have.end(),original.have.begin(),original.have.end());
    temp.have.insert(temp.have.end(),other.have.begin(),other.have.end());

    temp.sold.insert(temp.sold.end(),original.sold.begin(),original.sold.end());
    temp.sold.insert(temp.sold.end(),other.sold.begin(),other.sold.end());

    return temp;
}

class ArtCollectionTest {
    // has access to private members of ArtCollection
    private:
        ArtCollection my_collection;
        vector<Artwork> test_artwork;
        vector<SoldArtwork> test_soldArtwork;
    public:
		// test runner
        void run() {
        	cout << "1. Inserting artwork (should match) includes a duplicate" << endl;
            setup1();
            test_insert_artwork();
            reset();
            cout << endl << "2. Inserting artwork (should not match)" << endl;
            setup2();
            test_insert_artwork();
            reset();
            cout << endl << "3. Selling artwork (should match) includes selling an artwork that does not exist" << endl;
            setup3();
            test_sell_artwork();
            cout << endl << "4. Comparing artworks and sold artworks (should match)" << endl;
            test_compare_art();
            reset();
			cout << endl << "5. Testing == and + operator of ArtCollection" << endl;
			test_operators();
            //+operator
            //==operator
        }
        // initialize objects used in testing
        void setup1() {
	        Artwork a2("Evan", "bikes", 1996);
	    	Artwork a3("Keiquang", "integrals", 2020);
	    	test_artwork.push_back(a2);
			test_artwork.push_back(a3);
			my_collection.insert_artwork(a2);
            my_collection.insert_artwork(a2);
			my_collection.insert_artwork(a3);
        }
        void setup2() {
			Artwork a1("Jeremy", "number 1", 2020);
			Artwork a2("Evan", "bikes", 1996);
	    	Artwork a3("Keiquang", "integrals", 2020);
	    	test_artwork.push_back(a1);
        }
        
        void setup3() {
        	Artwork a1("Jeremy", "number 1", 2020);
        	Artwork a2("Evan", "bikes", 1996);
	    	Artwork a3("Keiquang", "integrals", 2020);
        	my_collection.insert_artwork(a1);
			SoldArtwork s1(a1, "joe", "joe's house", 0);
			my_collection.sell_artwork(s1);
			test_soldArtwork.push_back(s1);
			my_collection.sell_artwork(s1);
		}
		
        void reset() {
        	int have_size = my_collection.have.size(),
        		test_artwork_size = test_artwork.size(),
        		sold_size = my_collection.sold.size(),
        		test_soldArtwork_size = test_soldArtwork.size();
        	for (int clear = 0; clear < have_size; clear++)
        		my_collection.have.pop_back();
         	for (int clear = 0; clear < test_artwork_size; clear++)
        		test_artwork.pop_back();
			for (int clear = 0; clear < sold_size; clear++)
        		my_collection.sold.pop_back();
        	for (int clear = 0; clear < test_soldArtwork_size; clear++)
        		test_soldArtwork.pop_back();
			}
			
	    void test_insert_artwork(){
	        if(my_collection.have == test_artwork) {
	            cout << "Artwork inventories match!" << endl;
	        }
	        else
	            cout << "Artwork inventories do not match." << endl;
	    }
	
	    void test_sell_artwork(){
	        if(my_collection.sold == test_soldArtwork)
	             cout << "Sold artwork inventories match!" << endl;
	        else
	        	cout << "Sold artwork inventories do not match." << endl;
	    }
	
	    void test_compare_art(){
	    	Artwork a1("Keiquang", "integrals", 2020);
	    	Artwork a2("Keiquang", "integrals", 2020);
	    	Artwork a3("Timmy", "fairies", 2004);
	    	SoldArtwork x(a1, "bob", "bob's house", 20);
			SoldArtwork y(a2, "bob", "bob's house", 20);
			SoldArtwork z(a3, "joe", "joe's house", 0);
	        if (x==y&&!(x==z))
	        //sold artwork operator calls on the overloaded opertor== of artwork
	        //thus this test proves both operate correctly
	        	cout<<"Correct comparison." << endl;
	        else
	        	cout<<"Incorrect comparison."<< endl;
		}
        void test_operators(){
            ArtCollection total,temp;
            Artwork a1("Keiquang", "integrals", 2020);
	    	Artwork a2("mike", "this assignment hurts", 1997);
	    	Artwork a3("Timmy", "fairies", 2004);
			total.insert_artwork(a1);
            total.insert_artwork(a2);
            total.insert_artwork(a3);
            temp.insert_artwork(a1);
            my_collection.insert_artwork(a2);
            my_collection.insert_artwork(a3);
    		if ((total == (my_collection + temp)) && !(total == temp)){
				cout<<"Operators worked.";
			}
			else{
				cout<<"Operators did not work.";
			}
        }
		
};
int main()
{
    ArtCollectionTest test_collection;
    test_collection.run();
       
}

