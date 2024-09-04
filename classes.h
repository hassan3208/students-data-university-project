using namespace std;

class student {
public:
	int id;
	string name;
	int math, science, english, history, geography;
	float percentage;

	student(int id = -1, string name = "unknown", int math = 0, int science = 0, int english = 0, int history = 0, int geography = 0, float percentage = 0.0) {
		this->id = id;
		this->name = name;
		this->math = math;
		this->science = science;
		this->english = english;
		this->history = history;
		this->geography = geography;
		this->percentage = percentage;
	}

	void display() {
		cout << id << "\t" << name << "\t" << math << "\t" << science << "\t" << english << "\t" << history << "\t" << geography << "\t" << percentage << "\n";
	}
};

int countrows(string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "not found file" << endl;
		return 0;
	}

	string line;
	int numrows = 0;
	while (getline(file, line)) {
		numrows++;
	}
	file.close();
	return numrows - 1;
}

student* structure(string& filename, int numstudents) {

	if (numstudents < 1) {
		cerr << "No student data in file or unable to open file" << endl;
		return nullptr;
	}


	student* detail = new student[numstudents];
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "not open file" << endl;
		delete[] detail;
		return nullptr;
	}

	string line;
	int i = 0;


	getline(file, line);

	while (getline(file, line) && i < numstudents) {
		int pos = 0;
		string temp;


		pos = line.find(',');
		temp = line.substr(0, pos);
		int id = stoi(temp);
		line.erase(0, pos + 1);


		pos = line.find(',');
		string name = line.substr(0, pos);
		line.erase(0, pos + 1);


		pos = line.find(',');
		temp = line.substr(0, pos);
		int math = stoi(temp);
		line.erase(0, pos + 1);


		pos = line.find(',');
		temp = line.substr(0, pos);
		int science = stoi(temp);
		line.erase(0, pos + 1);


		pos = line.find(',');
		temp = line.substr(0, pos);
		int english = stoi(temp);
		line.erase(0, pos + 1);


		pos = line.find(',');
		temp = line.substr(0, pos);
		int history = stoi(temp);
		line.erase(0, pos + 1);


		pos = line.find(',');
		temp = line.substr(0, pos);
		int geography = stoi(temp);
		line.erase(0, pos + 1);


		temp = line;
		float percentage = stof(temp);

		detail[i++] = student(id, name, math, science, english, history, geography, percentage);

	}

	file.close();
	return detail;
}

class Node {
public:
	student key;
	Node* left;
	Node* right;
	int height;

	Node(student& key){
		this->key = key;
		left = nullptr;
		right = nullptr;
		height = 0;
	}
};

class avltree {
private:
	Node* root;

	int height(Node* n) {
		return n == nullptr ? 0 : n->height;
	}

	int max(int a, int b) {
		return a > b ? a : b;
	}

	Node* rightrotate(Node* unbalance) {
		Node* newn = unbalance->left;
		Node* t = newn->right;

		newn->right = unbalance;
		unbalance->left = t;

		unbalance->height = max(height(unbalance->left), height(unbalance->right));
		newn->height = max(height(newn->left), height(newn->right));//c

		return newn;
	}

	Node* leftrotate(Node* unbalance) {
		Node* New = unbalance->right;
		Node* t = New->left;

		New->left = unbalance;
		unbalance->right = t;

		unbalance->height = max(height(unbalance->left), height(unbalance->right)) + 1;
		New->height = max(height(New->left), height(New->right)) + 1;

		return New;
	}

	int getbalance(Node* n) {
		return n == nullptr ? 0 : height(n->left) - height(n->right);
	}

	Node* insert(Node* node, student& key) {
		if (node == nullptr){
			return new Node(key);
		}

		if (key.id < node->key.id)
			node->left = insert(node->left, key);
		else if (key.id > node->key.id)
			node->right = insert(node->right, key);
		else{
			cout << "\nanother student also has the same id as you enter\ntwo students cannot have same ids\n\n\n";
			return node;
		}


		node->height = 1 + max(height(node->left), height(node->right));

		int balance = getbalance(node);

		if (balance > 1 && key.id < node->left->key.id)
			return rightrotate(node);

		if (balance < -1 && key.id > node->right->key.id)
			return leftrotate(node);

		if (balance > 1 && key.id > node->left->key.id) {
			node->left = leftrotate(node->left);
			return rightrotate(node);
		}

		if (balance < -1 && key.id < node->right->key.id) {
			node->right = rightrotate(node->right);
			return leftrotate(node);
		}

		return node;
	}

	Node* minvaluenode(Node* node) {
		Node* current = node;
		while (current->left != nullptr)
			current = current->left;
		return current;
	}

	Node* search(Node* root, int key) {
		if (root == nullptr || root->key.id == key)
			return root;
		if (root->key.id < key)
			return search(root->right, key);
		return search(root->left, key);
	}

	Node* deletenode(Node* root, int key) {


		if (root == nullptr)
			return root;

		if (key < root->key.id)
			root->left = deletenode(root->left, key);
		else if (key > root->key.id)
			root->right = deletenode(root->right, key);
		else {
			if ((root->left == nullptr) || (root->right == nullptr)) {
				Node* temp = root->left ? root->left : root->right;
				if (temp == nullptr) {
					temp = root;
					root = nullptr;
				}
				else
					*root = *temp;
				delete temp;
			}
			else {
				Node* temp = minvaluenode(root->right);
				root->key = temp->key;
				root->right = deletenode(root->right, temp->key.id);
			}
		}

		if (root == nullptr)
			return root;

		root->height = 1 + max(height(root->left), height(root->right));

		int balance = getbalance(root);

		if (balance > 1 && getbalance(root->left) >= 0)
			return rightrotate(root);

		if (balance > 1 && getbalance(root->left) < 0) {
			root->left = leftrotate(root->left);
			return rightrotate(root);
		}

		if (balance < -1 && getbalance(root->right) <= 0)
			return leftrotate(root);

		if (balance < -1 && getbalance(root->right) > 0) {
			root->right = rightrotate(root->right);
			return leftrotate(root);
		}

		return root;
	}




	void preorder(Node* root) {
		if (root != nullptr) {
			preorder(root->left);
			root->key.display();
			preorder(root->right);
		}
	}



	Node* update(Node* node, int id, int num, int upd_marks) {
		if (node == nullptr) {
			return nullptr;
		}

		if (id < node->key.id) {
			node->left = update(node->left, id, num, upd_marks);
		}
		else if (id > node->key.id) {
			node->right = update(node->right, id, num, upd_marks);
		}
		else {
			// Update marks
			if (num == 1)
				node->key.math = upd_marks;
			else if (num == 2)
				node->key.science = upd_marks;
			else if (num == 3)
				node->key.english = upd_marks;
			else if (num == 4)
				node->key.history = upd_marks;
			else if (num == 5)
				node->key.geography = upd_marks;

			node->key.percentage = (node->key.math + node->key.science + node->key.english + node->key.history + node->key.geography) / 5.0;
		}

	
		node->height = 1 + max(height(node->left), height(node->right));
		int balance = getbalance(node);

		
		if (balance > 1 && getbalance(node->left) >= 0)
			return rightrotate(node);

		if (balance > 1 && getbalance(node->left) < 0) {
			node->left = leftrotate(node->left);
			return rightrotate(node);
		}

		if (balance < -1 && getbalance(node->right) <= 0)
			return leftrotate(node);

		if (balance < -1 && getbalance(node->right) > 0) {
			node->right = rightrotate(node->right);
			return leftrotate(node);
		}

		return node;
	}


public:
	avltree() : root(nullptr) {

	}

	void insert(student& key) {
		root = insert(root, key);
	}

	void deletenode(int key) {
		root = deletenode(root, key);
	}

	bool search(int key) {
		return search(root, key) != nullptr;
	}

	void preorder() {
		preorder(root);
		cout << endl;
	}

	Node *update(int id, int num, int upd_marks) {
		return update(root, id, num, upd_marks);
	}

	friend void searchstudent(avltree& tree);
	friend void savefile(avltree &tree);
	friend void update(avltree& tree);
};

void displaymenu() {
	cout << "students marksheet operations menu:\n";
	cout << "1. insert a student\n";
	cout << "2. delete a student\n";
	cout << "3. search for a student\n";
	cout << "4. display all students\n";
	cout << "5. update a student\n";
	cout << "6. exit\n";
}

void insertstudent(avltree& tree) {
	int id, math, science, english, history, geography;
	string name;
	float percentage;

	cout << "enter student id: ";
	cin >> id;
	cin.ignore();

	cout << "enter student name: ";
	getline(cin, name);

	cout << "enter math marks: ";
	cin >> math;

	cout << "enter science marks: ";
	cin >> science;

	cout << "enter english marks: ";
	cin >> english;

	cout << "enter history marks: ";
	cin >> history;

	cout << "enter geography marks: ";
	cin >> geography;

	percentage = (math + science + english + history + geography) / 5.0;

	student newstudent(id, name, math, science, english, history, geography, percentage);
	tree.insert(newstudent);

}

void deletestudent(avltree& tree) {
	int id;
	cout << "enter student id to delete: ";
	cin >> id;

	tree.deletenode(id);
	cout << "student deleted successfully.\n";
}

void searchstudent(avltree& tree) {
	int id;
	cout << "enter student id to search: ";
	cin >> id;
	Node* result = tree.search(tree.root, id);
	if (result != nullptr) {
		cout << "student found. details:\n";
		result->key.display();
	}
	else {
		cout << "student not found.\n";
	}
}


void update(avltree& tree){
	int id;
	cout << "enter student id to update: ";
	cin >> id;

	if (tree.search(id)){
		cout << "\n1 : Mathematics\n";
		cout << "\n2 : Science\n";
		cout << "\n3 : English\n";
		cout << "\n4 : History\n";
		cout << "\n5 : Geography\n";
		int num, marks;
		cout << "\nenter a subject number to update marks : "; cin >> num;
		cout << "\nenter updated marks : "; cin >> marks;
		if (num <= 5 && num > 0){
			tree.root = tree.update(id, num, marks);
            //cout << data->key.id << " " << data->key.name << " " << data->key.math << " " << data->key.science << " " << data->key.english << " " << data->key.history << " " << data->key.geography << " " << data->key.percentage;
			//tree.deletenode(data->key.id);
			//student newstudent(data->key.id, data->key.name, data->key.math, data->key.science, data->key.english, data->key.history, data->key.geography, data->key.percentage);
			//tree.insert(data->key);
			cout << "\nmarks updated suceccfullly..\n";
		}
		else
		{
			cout << "\nyou enter invalid subject\n";
		}
	}
	else
	{
		cout << "\nyou enter invalid sID\n";
	}
}

void savehelper(Node* root, ofstream& file) {
	if (root == nullptr)
		return;

	savehelper(root->left, file);
	file << root->key.id << "," << root->key.name << "," << root->key.math << ","
		<< root->key.science << "," << root->key.english << "," << root->key.history << ","
		<< root->key.geography << "," << root->key.percentage << "\n";
	savehelper(root->right, file);
}


void savefile(avltree &tree) {
	ofstream file;
	file.open("saved_students.csv");
	if (!file.is_open()) {
		cerr << "unable to open file for saving." << endl;
		return;
	}

	file << "id,name,math,science,english,history,geography,percentage" << endl;
	savehelper(tree.root, file);

	file.close();

	cout << "student data saved successfully." << endl;
}



