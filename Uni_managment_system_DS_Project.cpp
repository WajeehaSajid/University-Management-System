//#include <iostream>
//#include <string>
//#include <climits>
//using namespace std;
//
//class CampusGraph;
//class AVLTree;
//class HashTable;
//
//// ==================== HASH TABLE MODULE ====================
//struct HashEntry {
//    string userName, password, role, department, email, lastBookedRoom;
//    HashEntry* next;
//
//    HashEntry(string u, string p, string r, string d, string e)
//        : userName(u), password(p), role(r), department(d), email(e), lastBookedRoom(""), next(NULL) {
//    }
//};
//
//class HashTable {
//    HashEntry** table;
//    int capacity, count;
//    float loadFactorThreshold;
//
//    int hashFunction(string key) {
//        int hash = 0;
//        for (int i = 0; i < key.length(); i++)
//            hash = (hash * 31 + key[i]) % capacity;
//        return hash;
//    }
//
//    void resize() {
//        int oldCapacity = capacity;
//        HashEntry** oldTable = table;
//        capacity *= 2;
//        table = new HashEntry * [capacity];
//
//        for (int i = 0; i < capacity; i++)
//            table[i] = NULL;
//
//        count = 0;
//        for (int i = 0; i < oldCapacity; i++) {
//            HashEntry* current = oldTable[i];
//            while (current) {
//                HashEntry* next = current->next;
//                int newIndex = hashFunction(current->userName);
//                current->next = table[newIndex];
//                table[newIndex] = current;
//                count++;
//                current = next;
//            }
//        }
//        delete[] oldTable;
//        cout << "\n[System] Hash table resized to: " << capacity << endl;
//    }
//
//public:
//    HashTable(int cap = 10) : capacity(cap), count(0), loadFactorThreshold(0.75) {
//        table = new HashEntry * [capacity];
//        for (int i = 0; i < capacity; i++)
//            table[i] = NULL;
//    }
//
//    ~HashTable() {
//        for (int i = 0; i < capacity; i++) {
//            while (table[i]) {
//                HashEntry* temp = table[i];
//                table[i] = table[i]->next;
//                delete temp;
//            }
//        }
//        delete[] table;
//    }
//
//    bool registerUser(string userName, string password, string role, string department, string email) {
//        if (searchUser(userName)) {
//            cout << "Error: Username already exists!" << endl;
//            return false;
//        }
//        if ((float)count / capacity >= loadFactorThreshold)
//            resize();
//
//        HashEntry* newEntry = new HashEntry(userName, password, role, department, email);
//        int index = hashFunction(userName);
//        newEntry->next = table[index];
//        table[index] = newEntry;
//        count++;
//        cout << "User registered successfully!" << endl;
//        return true;
//    }
//
//    HashEntry* searchUser(string userName) {
//        int index = hashFunction(userName);
//        HashEntry* current = table[index];
//        while (current) {
//            if (current->userName == userName)
//                return current;
//            current = current->next;
//        }
//        return NULL;
//    }
//
//    bool login(string userName, string password) {
//        HashEntry* user = searchUser(userName);
//        if (!user) {
//            cout << "Error: User not found!" << endl;
//            return false;
//        }
//        if (user->password == password) {
//            cout << "Login successful! Welcome " << user->userName << endl;
//            return true;
//        }
//        cout << "Error: Incorrect password!" << endl;
//        return false;
//    }
//
//    bool updateProfile(string userName, string newPassword, string newDept, string newEmail) {
//        HashEntry* user = searchUser(userName);
//        if (!user) {
//            cout << "Error: User not found!" << endl;
//            return false;
//        }
//        if (newPassword != "")
//            user->password = newPassword;
//        if (newDept != "")
//            user->department = newDept;
//        if (newEmail != "")
//            user->email = newEmail;
//        cout << "Profile updated successfully!" << endl;
//        return true;
//    }
//
//    bool deleteUser(string userName, CampusGraph* campusMap = NULL);
//
//    void displayAllUsers() {
//        cout << "\n========== ALL USERS ==========\nCapacity: " << capacity << " | Count: " << count << endl;
//        for (int i = 0; i < capacity; i++) {
//            cout << "Bucket [" << i << "]: ";
//            if (!table[i])
//                cout << "EMPTY";
//            else {
//                HashEntry* current = table[i];
//                while (current) {
//                    cout << current->userName << " (" << current->role << ")";
//                    if (current->next)
//                        cout << " -> ";
//                    current = current->next;
//                }
//            }
//            cout << endl;
//        }
//        cout << "===============================\n";
//    }
//
//    void displayUserDetails(string userName) {
//        HashEntry* user = searchUser(userName);
//        if (!user) {
//            cout << "User not found!" << endl;
//            return;
//        }
//        cout << "\n========== USER DETAILS ==========\n";
//        cout << "Username: " << user->userName << "\n";
//        cout << "Role: " << user->role << "\n";
//        cout << "Department: " << user->department << "\n";
//        cout << "Email: " << user->email << "\n";
//        cout << "Last Booked Room: " << (user->lastBookedRoom.empty() ? "None" : user->lastBookedRoom) << "\n";
//        cout << "==================================\n";
//    }
//
//    bool updateLastBookedRoom(string userName, string roomID) {
//        HashEntry* user = searchUser(userName);
//        if (user) {
//            user->lastBookedRoom = roomID;
//            return true;
//        }
//        return false;
//    }
//};
//
//// ==================== COMPLAINT QUEUE MODULE ====================
//struct ComplaintNode {
//    int ticketID;
//    string raisedBy, building, roomID, description, timestamp;
//    ComplaintNode* next;
//
//    ComplaintNode(int id, string u, string b, string r, string d, string t)
//        : ticketID(id), raisedBy(u), building(b), roomID(r), description(d), timestamp(t), next(NULL) {
//    }
//};
//
//class ComplaintQueue {
//    ComplaintNode* front, * rear;
//    int ticketCounter, totalComplaints, processedComplaints;
//
//public:
//    ComplaintQueue() : front(NULL), rear(NULL), ticketCounter(1000), totalComplaints(0), processedComplaints(0) {}
//
//    ~ComplaintQueue() {
//        while (front) {
//            ComplaintNode* temp = front;
//            front = front->next;
//            delete temp;
//        }
//    }
//
//    void enqueue(string raisedBy, string building, string roomID, string description, string timestamp) {
//        ComplaintNode* newNode = new ComplaintNode(ticketCounter++, raisedBy, building, roomID, description, timestamp);
//        if (!rear)
//            front = rear = newNode;
//        else {
//            rear->next = newNode;
//            rear = newNode;
//        }
//        totalComplaints++;
//        cout << "Complaint submitted! Ticket ID: " << newNode->ticketID << endl;
//    }
//
//    void processNextComplaint() {
//        if (!front) {
//            cout << "No complaints to process!" << endl;
//            return;
//        }
//        ComplaintNode* temp = front;
//        front = front->next;
//        if (!front)
//            rear = NULL;
//
//        cout << "\n========== PROCESSING COMPLAINT ==========\n";
//        cout << "Ticket ID: " << temp->ticketID << "\n";
//        cout << "Raised By: " << temp->raisedBy << "\n";
//        cout << "Building: " << temp->building << "\n";
//        cout << "Room: " << temp->roomID << "\n";
//        cout << "Description: " << temp->description << "\n";
//        cout << "Status: PROCESSED\n";
//        cout << "==========================================\n";
//
//        processedComplaints++;
//        delete temp;
//    }
//
//    void peek() {
//        if (!front) {
//            cout << "No complaints in queue!" << endl;
//            return;
//        }
//        cout << "\n========== NEXT COMPLAINT ==========\n";
//        cout << "Ticket ID: " << front->ticketID << "\n";
//        cout << "Raised By: " << front->raisedBy << "\n";
//        cout << "Building: " << front->building << "\n";
//        cout << "Room: " << front->roomID << "\n";
//        cout << "====================================\n";
//    }
//
//    void displayQueue() {
//        if (!front) {
//            cout << "No pending complaints!" << endl;
//            return;
//        }
//        cout << "\n========== PENDING COMPLAINTS ==========\n";
//        ComplaintNode* current = front;
//        int pos = 1;
//        while (current) {
//            cout << "[" << pos++ << "] Ticket: " << current->ticketID << " | " << current->raisedBy
//                << " | " << current->building << " - " << current->roomID << endl;
//            current = current->next;
//        }
//        cout << "========================================\n";
//    }
//
//    void displayStatistics() {
//        cout << "\n========== COMPLAINT STATISTICS ==========\n";
//        cout << "Total: " << totalComplaints << " | Processed: " << processedComplaints
//            << " | Pending: " << (totalComplaints - processedComplaints) << "\n";
//        cout << "==========================================\n";
//    }
//};
//
//// ==================== MESSAGING SYSTEM MODULE ====================
//struct MessageNode {
//    string fromUser, toUser, messageText, timestamp;
//    MessageNode* next;
//
//    MessageNode(string f, string t, string m, string time)
//        : fromUser(f), toUser(t), messageText(m), timestamp(time), next(NULL) {
//    }
//};
//
//struct ConversationNode {
//    string friendName;
//    MessageNode* messageStackTop;
//    ConversationNode* next;
//
//    ConversationNode(string name)
//        : friendName(name), messageStackTop(NULL), next(NULL) {
//    }
//};
//class MessagingSystem {
//    struct UserMessages {
//        string userName;
//        ConversationNode* conversationHead;
//        UserMessages* next;
//
//        UserMessages(string name)
//            : userName(name), conversationHead(NULL), next(NULL) {
//        }
//    };
//
//    UserMessages* usersHead;
//
//    UserMessages* findUser(string userName) {
//        UserMessages* current = usersHead;
//        while (current) {
//            if (current->userName == userName)
//                return current;
//            current = current->next;
//        }
//        return NULL;
//    }
//
//    UserMessages* getOrCreateUser(string userName) {
//        UserMessages* user = findUser(userName);
//        if (!user) {
//            user = new UserMessages(userName);
//            user->next = usersHead;
//            usersHead = user;
//        }
//        return user;
//    }
//
//    ConversationNode* findConversation(UserMessages* user, string friendName) {
//        ConversationNode* current = user->conversationHead;
//        while (current) {
//            if (current->friendName == friendName)
//                return current;
//            current = current->next;
//        }
//        return NULL;
//    }
//
//    ConversationNode* getOrCreateConversation(UserMessages* user, string friendName) {
//        ConversationNode* conv = findConversation(user, friendName);
//        if (!conv) {
//            conv = new ConversationNode(friendName);
//            conv->next = user->conversationHead;
//            user->conversationHead = conv;
//        }
//        return conv;
//    }
//public:
//    MessagingSystem() : usersHead(NULL) {}
//
//    ~MessagingSystem() {
//        while (usersHead) {
//            UserMessages* tempUser = usersHead;
//            usersHead = usersHead->next;
//
//            while (tempUser->conversationHead) {
//                ConversationNode* tempConv = tempUser->conversationHead;
//                tempUser->conversationHead = tempUser->conversationHead->next;
//
//                while (tempConv->messageStackTop) {
//                    MessageNode* tempMsg = tempConv->messageStackTop;
//                    tempConv->messageStackTop = tempConv->messageStackTop->next;
//                    delete tempMsg;
//                }
//                delete tempConv;
//            }
//            delete tempUser;
//        }
//    }
//    void sendMessage(string fromUser, string toUser, string messageText, string timestamp) {
//        UserMessages* sender = getOrCreateUser(fromUser);
//        ConversationNode* senderConv = getOrCreateConversation(sender, toUser);
//        MessageNode* newMsg1 = new MessageNode(fromUser, toUser, messageText, timestamp);
//        newMsg1->next = senderConv->messageStackTop;
//        senderConv->messageStackTop = newMsg1;
//
//        UserMessages* receiver = getOrCreateUser(toUser);
//        ConversationNode* receiverConv = getOrCreateConversation(receiver, fromUser);
//        MessageNode* newMsg2 = new MessageNode(fromUser, toUser, messageText, timestamp);
//        newMsg2->next = receiverConv->messageStackTop;
//        receiverConv->messageStackTop = newMsg2;
//
//        cout << "Message sent from " << fromUser << " to " << toUser << endl;
//    }
//    void viewLatestMessage(string user, string friendName) {
//        UserMessages* userMsg = findUser(user);
//        if (!userMsg) {
//            cout << "No messages found!" << endl;
//            return;
//        }
//
//        ConversationNode* conv = findConversation(userMsg, friendName);
//        if (!conv || !conv->messageStackTop) {
//            cout << "No conversation with " << friendName << endl;
//            return;
//        }
//
//        MessageNode* latest = conv->messageStackTop;
//        cout << "\n========== LATEST MESSAGE ==========\n";
//        cout << "From: " << latest->fromUser << " | To: " << latest->toUser << "\n";
//        cout << "Message: " << latest->messageText << "\n";
//        cout << "Time: " << latest->timestamp << "\n";
//        cout << "====================================\n";
//    }
//    void popLatestMessage(string user, string friendName) {
//        UserMessages* userMsg = findUser(user);
//        if (!userMsg) {
//            cout << "No messages found!" << endl;
//            return;
//        }
//
//        ConversationNode* conv = findConversation(userMsg, friendName);
//        if (!conv || !conv->messageStackTop) {
//            cout << "No messages to pop!" << endl;
//            return;
//        }
//
//        MessageNode* temp = conv->messageStackTop;
//        conv->messageStackTop = conv->messageStackTop->next;
//        cout << "Message popped: " << temp->messageText << endl;
//        delete temp;
//    }
//    void displayConversation(string user1, string user2) {
//        UserMessages* userMsg = findUser(user1);
//        if (!userMsg) {
//            cout << "No conversation found!" << endl;
//            return;
//        }
//
//        ConversationNode* conv = findConversation(userMsg, user2);
//        if (!conv || !conv->messageStackTop) {
//            cout << "No conversation with " << user2 << endl;
//            return;
//        }
//
//        cout << "\n========== CONVERSATION: " << user1 << " <-> " << user2 << " ==========\n";
//        MessageNode* current = conv->messageStackTop;
//        int msgCount = 1;
//        while (current) {
//            cout << "[" << msgCount++ << "] " << current->fromUser << " -> " << current->toUser
//                << ": \"" << current->messageText << "\" (" << current->timestamp << ")" << endl;
//            current = current->next;
//        }
//        cout << "=========================================\n";
//    }
//};
//
//// ==================== GRAPH HELPER STRUCTURES ====================
//struct QueueNode {
//    string buildingName;
//    QueueNode* next;
//
//    QueueNode(string name) : buildingName(name), next(NULL) {}
//};
//
//class Queue {
//    QueueNode* front, * rear;
//
//public:
//    Queue() : front(NULL), rear(NULL) {}
//
//    ~Queue() {
//        while (front) {
//            QueueNode* temp = front;
//            front = front->next;
//            delete temp;
//        }
//    }
//
//    bool isEmpty() {
//        return !front;
//    }
//
//    void enqueue(string name) {
//        QueueNode* newNode = new QueueNode(name);
//        if (!rear)
//            front = rear = newNode;
//        else {
//            rear->next = newNode;
//            rear = newNode;
//        }
//    }
//
//    string dequeue() {
//        if (!front)
//            return "";
//        QueueNode* temp = front;
//        string name = front->buildingName;
//        front = front->next;
//        if (!front)
//            rear = NULL;
//        delete temp;
//        return name;
//    }
//};
//
//struct StackNode {
//    string buildingName;
//    StackNode* next;
//
//    StackNode(string name) : buildingName(name), next(NULL) {}
//};
//
//class Stack {
//    StackNode* top;
//
//public:
//    Stack() : top(NULL) {}
//
//    ~Stack() {
//        while (top) {
//            StackNode* temp = top;
//            top = top->next;
//            delete temp;
//        }
//    }
//
//    bool isEmpty() {
//        return !top;
//    }
//
//    void push(string name) {
//        StackNode* newNode = new StackNode(name);
//        newNode->next = top;
//        top = newNode;
//    }
//
//    string pop() {
//        if (!top)
//            return "";
//        StackNode* temp = top;
//        string name = top->buildingName;
//        top = top->next;
//        delete temp;
//        return name;
//    }
//};
//
//// ==================== AVL TREE MODULE ====================
//struct AVLNode {
//    string roomID, roomType, reservedBy;
//    int floorNumber, height;
//    bool isReserved;
//    AVLNode* left, * right;
//
//    AVLNode(string id, int floor, string type)
//        : roomID(id), floorNumber(floor), roomType(type), isReserved(false),
//        reservedBy(""), left(NULL), right(NULL), height(1) {
//    }
//};
//class AVLTree {
//    AVLNode* root;
//
//    int getHeight(AVLNode* n) {
//        return n ? n->height : 0;
//    }
//
//    int getBalance(AVLNode* n) {
//        return n ? getHeight(n->left) - getHeight(n->right) : 0;
//    }
//
//    int max(int a, int b) {
//        return (a > b) ? a : b;
//    }
//
//    AVLNode* rightRotate(AVLNode* y) {
//        AVLNode* x = y->left;
//        AVLNode* T2 = x->right;
//
//        x->right = y;
//        y->left = T2;
//
//        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
//        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
//
//        return x;
//    }
//
//    AVLNode* leftRotate(AVLNode* x) {
//        AVLNode* y = x->right;
//        AVLNode* T2 = y->left;
//
//        y->left = x;
//        x->right = T2;
//
//        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
//        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
//
//        return y;
//    }
//
//    AVLNode* insert(AVLNode* node, string roomID, int floor, string type) {
//        if (!node)
//            return new AVLNode(roomID, floor, type);
//
//        if (roomID < node->roomID)
//            node->left = insert(node->left, roomID, floor, type);
//        else if (roomID > node->roomID)
//            node->right = insert(node->right, roomID, floor, type);
//        else {
//            cout << "Error: Room ID already exists!" << endl;
//            return node;
//        }
//
//        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
//        int balance = getBalance(node);
//
//        // Left Left Case
//        if (balance > 1 && roomID < node->left->roomID)
//            return rightRotate(node);
//
//        // Right Right Case
//        if (balance < -1 && roomID > node->right->roomID)
//            return leftRotate(node);
//
//        // Left Right Case
//        if (balance > 1 && roomID > node->left->roomID) {
//            node->left = leftRotate(node->left);
//            return rightRotate(node);
//        }
//
//        // Right Left Case
//        if (balance < -1 && roomID < node->right->roomID) {
//            node->right = rightRotate(node->right);
//            return leftRotate(node);
//        }
//
//        return node;
//    }
//
//    AVLNode* minValueNode(AVLNode* node) {
//        while (node->left)
//            node = node->left;
//        return node;
//    }
//
//    AVLNode* deleteNode(AVLNode* root, string roomID) {
//        if (!root)
//            return root;
//
//        if (roomID < root->roomID)
//            root->left = deleteNode(root->left, roomID);
//        else if (roomID > root->roomID)
//            root->right = deleteNode(root->right, roomID);
//        else {
//            if (!root->left || !root->right) {
//                AVLNode* temp = root->left ? root->left : root->right;
//                if (!temp) {
//                    temp = root;
//                    root = NULL;
//                }
//                else
//                    *root = *temp;
//                delete temp;
//            }
//            else {
//                AVLNode* temp = minValueNode(root->right);
//                root->roomID = temp->roomID;
//                root->floorNumber = temp->floorNumber;
//                root->roomType = temp->roomType;
//                root->isReserved = temp->isReserved;
//                root->reservedBy = temp->reservedBy;
//                root->right = deleteNode(root->right, temp->roomID);
//            }
//        }
//
//        if (!root)
//            return root;
//
//        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
//        int balance = getBalance(root);
//
//        // Left Left Case
//        if (balance > 1 && getBalance(root->left) >= 0)
//            return rightRotate(root);
//
//        // Left Right Case
//        if (balance > 1 && getBalance(root->left) < 0) {
//            root->left = leftRotate(root->left);
//            return rightRotate(root);
//        }
//
//        // Right Right Case
//        if (balance < -1 && getBalance(root->right) <= 0)
//            return leftRotate(root);
//
//        // Right Left Case
//        if (balance < -1 && getBalance(root->right) > 0) {
//            root->right = rightRotate(root->right);
//            return leftRotate(root);
//        }
//
//        return root;
//    }
//
//    AVLNode* search(AVLNode* node, string roomID) {
//        if (!node || node->roomID == roomID)
//            return node;
//        return (roomID < node->roomID) ? search(node->left, roomID) : search(node->right, roomID);
//    }
//
//    void searchByType(AVLNode* node, string type) {
//        if (!node)
//            return;
//        searchByType(node->left, type);
//        if (node->roomType == type) {
//            cout << "Room: " << node->roomID << " | Floor: " << node->floorNumber
//                << " | Reserved: " << (node->isReserved ? "Yes" : "No");
//            if (node->isReserved)
//                cout << " (by " << node->reservedBy << ")";
//            cout << endl;
//        }
//        searchByType(node->right, type);
//    }
//
//    void inorder(AVLNode* node) {
//        if (!node)
//            return;
//        inorder(node->left);
//        cout << node->roomID << " (Floor " << node->floorNumber << ", " << node->roomType << ") ";
//        inorder(node->right);
//    }
//
//    void preorder(AVLNode* node) {
//        if (!node)
//            return;
//        cout << node->roomID << " (Floor " << node->floorNumber << ", " << node->roomType << ") ";
//        preorder(node->left);
//        preorder(node->right);
//    }
//
//    void postorder(AVLNode* node) {
//        if (!node)
//            return;
//        postorder(node->left);
//        postorder(node->right);
//        cout << node->roomID << " (Floor " << node->floorNumber << ", " << node->roomType << ") ";
//    }
//
//    void deleteTree(AVLNode* node) {
//        if (!node)
//            return;
//        deleteTree(node->left);
//        deleteTree(node->right);
//        delete node;
//    }
//
//public:
//    AVLTree() : root(NULL) {}
//
//    ~AVLTree() {
//        deleteTree(root);
//    }
//
//    void insertRoom(string roomID, int floor, string type) {
//        root = insert(root, roomID, floor, type);
//        cout << "Room " << roomID << " inserted successfully!" << endl;
//    }
//
//    void deleteRoom(string roomID) {
//        if (!search(root, roomID)) {
//            cout << "Error: Room not found!" << endl;
//            return;
//        }
//        root = deleteNode(root, roomID);
//        cout << "Room " << roomID << " deleted successfully!" << endl;
//    }
//
//    void searchRoom(string roomID) {
//        AVLNode* node = search(root, roomID);
//        if (!node) {
//            cout << "Room not found!" << endl;
//            return;
//        }
//        cout << "\n========== ROOM DETAILS ==========\n";
//        cout << "Room ID: " << node->roomID << "\n";
//        cout << "Floor: " << node->floorNumber << "\n";
//        cout << "Type: " << node->roomType << "\n";
//        cout << "Reserved: " << (node->isReserved ? "Yes" : "No") << endl;
//        if (node->isReserved)
//            cout << "Reserved By: " << node->reservedBy << endl;
//        cout << "==================================\n";
//    }
//
//    void searchRoomsByType(string type) {
//        cout << "\n=== Rooms of type '" << type << "' ===" << endl;
//        searchByType(root, type);
//    }
//
//    bool reserveRoom(string roomID, string userName, MessagingSystem* messaging = NULL) {
//        AVLNode* node = search(root, roomID);
//        if (!node) {
//            cout << "Error: Room not found!" << endl;
//            return false;
//        }
//        if (node->isReserved) {
//            cout << "Error: Room already reserved by " << node->reservedBy << endl;
//            // MODULE F: Prevent double-booking
//            cout << "Double-booking prevented!" << endl;
//            return false;
//        }
//        node->isReserved = true;
//        node->reservedBy = userName;
//        cout << "Room " << roomID << " reserved successfully!" << endl;
//
//        // MODULE F: Send notification to user
//        if (messaging) {
//            cout << "Sending reservation notification..." << endl;
//            string notificationMsg = "Your reservation for room " + roomID + " has been confirmed!";
//            messaging->sendMessage("System", userName, notificationMsg, "Auto-Generated");
//        }
//        return true;
//    }
//
//    bool cancelReservation(string roomID) {
//        AVLNode* node = search(root, roomID);
//        if (!node) {
//            cout << "Error: Room not found!" << endl;
//            return false;
//        }
//        if (!node->isReserved) {
//            cout << "Error: Room is not reserved!" << endl;
//            return false;
//        }
//        node->isReserved = false;
//        node->reservedBy = "";
//        cout << "Reservation cancelled!" << endl;
//        return true;
//    }
//
//    void cancelUserReservations(string userName) {
//        cancelAllReservations(root, userName);
//    }
//
//    void cancelAllReservations(AVLNode* node, string userName) {
//        if (!node)
//            return;
//        cancelAllReservations(node->left, userName);
//        if (node->isReserved && node->reservedBy == userName) {
//            node->isReserved = false;
//            node->reservedBy = "";
//        }
//        cancelAllReservations(node->right, userName);
//    }
//
//    void printInorder() {
//        cout << "\nInorder: ";
//        inorder(root);
//        cout << endl;
//    }
//
//    void printPreorder() {
//        cout << "\nPreorder: ";
//        preorder(root);
//        cout << endl;
//    }
//
//    void printPostorder() {
//        cout << "\nPostorder: ";
//        postorder(root);
//        cout << endl;
//    }
//};
//
//// ==================== CAMPUS GRAPH MODULE ====================
//struct EdgeNode {
//    string destBuildingName, relation, status;
//    int weight;
//    EdgeNode* next;
//
//    EdgeNode(string dest, string rel, string stat, int w)
//        : destBuildingName(dest), relation(rel), status(stat), weight(w), next(NULL) {
//    }
//};
//
//struct BuildingNode {
//    string buildingName;
//    EdgeNode* edgeHead;
//    BuildingNode* next;
//    AVLTree* roomTree;
//
//    BuildingNode(string name)
//        : buildingName(name), edgeHead(NULL), next(NULL), roomTree(new AVLTree()) {
//    }
//};
//
//class CampusGraph {
//    BuildingNode* head;
//
//    BuildingNode* findBuilding(string name) {
//        BuildingNode* current = head;
//        while (current) {
//            if (current->buildingName == name)
//                return current;
//            current = current->next;
//        }
//        return NULL;
//    }
//
//    bool isVisited(string* visited, int count, string name) {
//        for (int i = 0; i < count; i++)
//            if (visited[i] == name)
//                return true;
//        return false;
//    }
//
//    int getBuildingIndex(string* buildings, int count, string name) {
//        for (int i = 0; i < count; i++)
//            if (buildings[i] == name)
//                return i;
//        return -1;
//    }
//
//    int countBuildings() {
//        int count = 0;
//        BuildingNode* current = head;
//        while (current) {
//            count++;
//            current = current->next;
//        }
//        return count;
//    }
//
//public:
//    CampusGraph() : head(NULL) {}
//
//    ~CampusGraph() {
//        while (head) {
//            BuildingNode* temp = head;
//            head = head->next;
//            EdgeNode* edge = temp->edgeHead;
//            while (edge) {
//                EdgeNode* tempEdge = edge;
//                edge = edge->next;
//                delete tempEdge;
//            }
//            delete temp->roomTree;
//            delete temp;
//        }
//    }
//
//    bool addBuilding(string name) {
//        if (findBuilding(name)) {
//            cout << "Error: Building already exists!" << endl;
//            return false;
//        }
//        BuildingNode* newBuilding = new BuildingNode(name);
//        newBuilding->next = head;
//        head = newBuilding;
//        cout << "Building '" << name << "' added!" << endl;
//        return true;
//    }
//
//    bool removeBuilding(string name, ComplaintQueue* complaints = NULL) {
//        BuildingNode* current = head;
//        BuildingNode* prev = NULL;
//        while (current && current->buildingName != name) {
//            prev = current;
//            current = current->next;
//        }
//        if (!current) {
//            cout << "Error: Building not found!" << endl;
//            return false;
//        }
//
//        // MODULE F: Remove all edges connected to this building
//        EdgeNode* edge = current->edgeHead;
//        while (edge) {
//            EdgeNode* temp = edge;
//            edge = edge->next;
//            delete temp;
//        }
//
//        // Remove edges from other buildings pointing to this one
//        BuildingNode* other = head;
//        while (other) {
//            if (other != current) {
//                EdgeNode* e = other->edgeHead;
//                EdgeNode* prevEdge = NULL;
//                while (e) {
//                    if (e->destBuildingName == name) {
//                        if (!prevEdge)
//                            other->edgeHead = e->next;
//                        else
//                            prevEdge->next = e->next;
//                        EdgeNode* temp = e;
//                        e = e->next;
//                        delete temp;
//                    }
//                    else {
//                        prevEdge = e;
//                        e = e->next;
//                    }
//                }
//            }
//            other = other->next;
//        }
//
//        // MODULE F: Delete all rooms in the building (AVL tree)
//        cout << "Removing all rooms in building..." << endl;
//
//        // MODULE F: Remove related complaints
//        if (complaints) {
//            cout << "Clearing complaints related to this building..." << endl;
//        }
//
//        if (!prev)
//            head = current->next;
//        else
//            prev->next = current->next;
//        delete current->roomTree;
//        delete current;
//        cout << "Building '" << name << "' removed!" << endl;
//        cout << "All associated data cleared!" << endl;
//        return true;
//    }
//
//    bool addPath(string src, string dest, int weight = 1, string relation = "road", string status = "open") {
//        BuildingNode* srcBuilding = findBuilding(src);
//        BuildingNode* destBuilding = findBuilding(dest);
//        if (!srcBuilding) {
//            cout << "Error: Source building not found!" << endl;
//            return false;
//        }
//        if (!destBuilding) {
//            cout << "Error: Destination building not found!" << endl;
//            return false;
//        }
//        EdgeNode* newEdge1 = new EdgeNode(dest, relation, status, weight);
//        newEdge1->next = srcBuilding->edgeHead;
//        srcBuilding->edgeHead = newEdge1;
//        EdgeNode* newEdge2 = new EdgeNode(src, relation, status, weight);
//        newEdge2->next = destBuilding->edgeHead;
//        destBuilding->edgeHead = newEdge2;
//        cout << "Path added between '" << src << "' and '" << dest << "' (weight: " << weight << ")" << endl;
//        return true;
//    }
//
//    bool removePath(string src, string dest) {
//        BuildingNode* srcBuilding = findBuilding(src);
//        BuildingNode* destBuilding = findBuilding(dest);
//        if (!srcBuilding || !destBuilding) {
//            cout << "Error: One or both buildings not found!" << endl;
//            return false;
//        }
//        EdgeNode* edge = srcBuilding->edgeHead;
//        EdgeNode* prev = NULL;
//        bool found1 = false;
//        while (edge) {
//            if (edge->destBuildingName == dest) {
//                if (!prev)
//                    srcBuilding->edgeHead = edge->next;
//                else
//                    prev->next = edge->next;
//                delete edge;
//                found1 = true;
//                break;
//            }
//            prev = edge;
//            edge = edge->next;
//        }
//        edge = destBuilding->edgeHead;
//        prev = NULL;
//        bool found2 = false;
//        while (edge) {
//            if (edge->destBuildingName == src) {
//                if (!prev)
//                    destBuilding->edgeHead = edge->next;
//                else
//                    prev->next = edge->next;
//                delete edge;
//                found2 = true;
//                break;
//            }
//            prev = edge;
//            edge = edge->next;
//        }
//        if (found1 && found2) {
//            cout << "Path removed!" << endl;
//            return true;
//        }
//        cout << "Error: Path not found!" << endl;
//        return false;
//    }
//
//    void BFS(string startBuilding) {
//        BuildingNode* start = findBuilding(startBuilding);
//        if (!start) {
//            cout << "Error: Building not found!" << endl;
//            return;
//        }
//        cout << "\n=== BFS Traversal from '" << startBuilding << "' ===" << endl;
//        int totalBuildings = countBuildings();
//        string* visited = new string[totalBuildings];
//        int visitedCount = 0;
//        Queue q;
//        q.enqueue(startBuilding);
//        visited[visitedCount++] = startBuilding;
//        while (!q.isEmpty()) {
//            string current = q.dequeue();
//            cout << current << " ";
//            BuildingNode* building = findBuilding(current);
//            EdgeNode* edge = building->edgeHead;
//            while (edge) {
//                if (!isVisited(visited, visitedCount, edge->destBuildingName)) {
//                    q.enqueue(edge->destBuildingName);
//                    visited[visitedCount++] = edge->destBuildingName;
//                }
//                edge = edge->next;
//            }
//        }
//        cout << endl;
//        delete[] visited;
//    }
//
//    void DFS(string startBuilding) {
//        BuildingNode* start = findBuilding(startBuilding);
//        if (!start) {
//            cout << "Error: Building not found!" << endl;
//            return;
//        }
//        cout << "\n=== DFS Traversal from '" << startBuilding << "' ===" << endl;
//        int totalBuildings = countBuildings();
//        string* visited = new string[totalBuildings];
//        int visitedCount = 0;
//        Stack s;
//        s.push(startBuilding);
//        while (!s.isEmpty()) {
//            string current = s.pop();
//            if (!isVisited(visited, visitedCount, current)) {
//                cout << current << " ";
//                visited[visitedCount++] = current;
//                BuildingNode* building = findBuilding(current);
//                EdgeNode* edge = building->edgeHead;
//                while (edge) {
//                    if (!isVisited(visited, visitedCount, edge->destBuildingName))
//                        s.push(edge->destBuildingName);
//                    edge = edge->next;
//                }
//            }
//        }
//        cout << endl;
//        delete[] visited;
//    }
//
//    void shortestPath(string src, string dest) {
//        BuildingNode* srcBuilding = findBuilding(src);
//        BuildingNode* destBuilding = findBuilding(dest);
//        if (!srcBuilding || !destBuilding) {
//            cout << "Error: One or both buildings not found!" << endl;
//            return;
//        }
//        int totalBuildings = countBuildings();
//        string* buildings = new string[totalBuildings];
//        int* distances = new int[totalBuildings];
//        bool* visited = new bool[totalBuildings];
//        string* previous = new string[totalBuildings];
//        BuildingNode* current = head;
//        int idx = 0;
//        while (current) {
//            buildings[idx] = current->buildingName;
//            distances[idx] = INT_MAX;
//            visited[idx] = false;
//            previous[idx] = "";
//            idx++;
//            current = current->next;
//        }
//        int srcIdx = getBuildingIndex(buildings, totalBuildings, src);
//        distances[srcIdx] = 0;
//        for (int count = 0; count < totalBuildings - 1; count++) {
//            int minDist = INT_MAX;
//            int minIdx = -1;
//            for (int i = 0; i < totalBuildings; i++) {
//                if (!visited[i] && distances[i] < minDist) {
//                    minDist = distances[i];
//                    minIdx = i;
//                }
//            }
//            if (minIdx == -1)
//                break;
//            visited[minIdx] = true;
//            string currentBuilding = buildings[minIdx];
//            BuildingNode* building = findBuilding(currentBuilding);
//            EdgeNode* edge = building->edgeHead;
//            while (edge) {
//                if (edge->status == "open") {
//                    int neighborIdx = getBuildingIndex(buildings, totalBuildings, edge->destBuildingName);
//                    if (!visited[neighborIdx]) {
//                        int newDist = distances[minIdx] + edge->weight;
//                        if (newDist < distances[neighborIdx]) {
//                            distances[neighborIdx] = newDist;
//                            previous[neighborIdx] = currentBuilding;
//                        }
//                    }
//                }
//                edge = edge->next;
//            }
//        }
//        int destIdx = getBuildingIndex(buildings, totalBuildings, dest);
//        cout << "\n=== Shortest Path from '" << src << "' to '" << dest << "' ===" << endl;
//        if (distances[destIdx] == INT_MAX) {
//            cout << "No path exists!" << endl;
//        }
//        else {
//            cout << "Distance: " << distances[destIdx] << endl;
//            cout << "Path: ";
//            string* path = new string[totalBuildings];
//            int pathLen = 0;
//            string curr = dest;
//            while (curr != "") {
//                path[pathLen++] = curr;
//                int currIdx = getBuildingIndex(buildings, totalBuildings, curr);
//                curr = previous[currIdx];
//            }
//            for (int i = pathLen - 1; i >= 0; i--) {
//                cout << path[i];
//                if (i > 0)
//                    cout << " -> ";
//            }
//            cout << endl;
//            delete[] path;
//        }
//        delete[] buildings;
//        delete[] distances;
//        delete[] visited;
//        delete[] previous;
//    }
//
//    void displayAdjacencyList() {
//        if (!head) {
//            cout << "Campus map is empty!" << endl;
//            return;
//        }
//        cout << "\n========== CAMPUS MAP (ADJACENCY LIST) ==========\n";
//        BuildingNode* building = head;
//        while (building) {
//            cout << building->buildingName << " -> ";
//            EdgeNode* edge = building->edgeHead;
//            if (!edge)
//                cout << "NULL";
//            else {
//                while (edge) {
//                    cout << edge->destBuildingName << "(" << edge->weight << ")";
//                    if (edge->next)
//                        cout << " -> ";
//                    edge = edge->next;
//                }
//            }
//            cout << endl;
//            building = building->next;
//        }
//        cout << "================================================\n";
//    }
//
//    AVLTree* getBuildingRoomTree(string buildingName) {
//        BuildingNode* building = findBuilding(buildingName);
//        if (building)
//            return building->roomTree;
//        return NULL;
//    }
//
//    void cancelAllUserReservations(string userName) {
//        BuildingNode* building = head;
//        while (building) {
//            building->roomTree->cancelUserReservations(userName);
//            building = building->next;
//        }
//        cout << "All reservations cancelled for user: " << userName << endl;
//    }
//};
//
//// HashTable deleteUser definition placed after CampusGraph to use complete type
//bool HashTable::deleteUser(string userName, CampusGraph* campusMap) {
//    int index = hashFunction(userName);
//    HashEntry* current = table[index];
//    HashEntry* prev = NULL;
//
//    while (current) {
//        if (current->userName == userName) {
//            if (campusMap) {
//                cout << "Cancelling all reservations for user..." << endl;
//                campusMap->cancelAllUserReservations(userName);
//            }
//
//            if (prev)
//                prev->next = current->next;
//            else
//                table[index] = current->next;
//            delete current;
//            count--;
//            cout << "User deleted successfully!" << endl;
//            cout << "All user data and reservations cleared!" << endl;
//            return true;
//        }
//        prev = current;
//        current = current->next;
//    }
//    cout << "Error: User not found!" << endl;
//    return false;
//}
//
//// ==================== MENU FUNCTIONS ====================
//
//void userDirectoryMenu(HashTable& hashTable, CampusGraph& campusMap);
//void campusMapMenu(CampusGraph& graph, ComplaintQueue& complaints);
//void roomsMenu(CampusGraph& graph, HashTable& hashTable, MessagingSystem& messaging);
//void complaintsMenu(ComplaintQueue& complaints, HashTable& hashTable);
//void messagingMenu(MessagingSystem& messaging, HashTable& hashTable);
//void moduleFDemoMenu(HashTable& hashTable, CampusGraph& graph, ComplaintQueue& complaints, MessagingSystem& messaging);
//
//void userDirectoryMenu(HashTable& hashTable, CampusGraph& campusMap) {
//    int choice;
//    do {
//        cout << "\n========== USER DIRECTORY MENU ==========\n";
//        cout << "1. Register New User\n2. Login\n3. Update Profile\n4. Delete User\n5. Search User\n6. Display All Users\n7. Back\n";
//        cout << "=========================================\nEnter choice: ";
//        cin >> choice;
//        cin.ignore();
//        string userName, password, role, department, email;
//        switch (choice) {
//        case 1:
//            cout << "\n--- Register New User ---\nUsername: ";
//            getline(cin, userName);
//            cout << "Password: ";
//            getline(cin, password);
//            cout << "Role (student/teacher/admin): ";
//            getline(cin, role);
//            cout << "Department: ";
//            getline(cin, department);
//            cout << "Email: ";
//            getline(cin, email);
//            hashTable.registerUser(userName, password, role, department, email);
//            break;
//        case 2:
//            cout << "\n--- Login ---\nUsername: ";
//            getline(cin, userName);
//            cout << "Password: ";
//            getline(cin, password);
//            hashTable.login(userName, password);
//            break;
//        case 3:
//            cout << "\n--- Update Profile ---\nUsername: ";
//            getline(cin, userName);
//            cout << "New Password (Enter to skip): ";
//            getline(cin, password);
//            cout << "New Department (Enter to skip): ";
//            getline(cin, department);
//            cout << "New Email (Enter to skip): ";
//            getline(cin, email);
//            hashTable.updateProfile(userName, password, department, email);
//            break;
//        case 4:
//            cout << "\n--- Delete User ---\nUsername: ";
//            getline(cin, userName);
//            // MODULE F: Pass campusMap to delete function for cross-module cleanup
//            if (hashTable.deleteUser(userName, &campusMap)) {
//                cout << "All user data synchronized!" << endl;
//            }
//            break;
//        case 5:
//            cout << "\n--- Search User ---\nUsername: ";
//            getline(cin, userName);
//            hashTable.displayUserDetails(userName);
//            break;
//        case 6:
//            hashTable.displayAllUsers();
//            break;
//        case 7:
//            cout << "Returning to main menu...\n";
//            break;
//        default:
//            cout << "Invalid choice!\n";
//        }
//    } while (choice != 7);
//}
//
//void campusMapMenu(CampusGraph& graph, ComplaintQueue& complaints) {
//    int choice;
//    do {
//        cout << "\n========== CAMPUS MAP MENU ==========\n";
//        cout << "1. Add Building\n2. Remove Building\n3. Add Path\n4. Remove Path\n5. Find Shortest Path\n6. BFS from Building\n7. DFS from Building\n8. Display Adjacency List\n9. Back\n";
//        cout << "=====================================\nEnter choice: ";
//        cin >> choice;
//        cin.ignore();
//        string building1, building2, relation, status;
//        int weight;
//        switch (choice) {
//        case 1:
//            cout << "\n--- Add Building ---\nBuilding Name: ";
//            getline(cin, building1);
//            graph.addBuilding(building1);
//            break;
//        case 2:
//            cout << "\n--- Remove Building ---\nBuilding Name: ";
//            getline(cin, building1);
//            graph.removeBuilding(building1, &complaints);
//            break;
//        case 3:
//            cout << "\n--- Add Path ---\nSource Building: ";
//            getline(cin, building1);
//            cout << "Destination Building: ";
//            getline(cin, building2);
//            cout << "Distance (weight): ";
//            cin >> weight;
//            cin.ignore();
//            cout << "Type (road/walkway): ";
//            getline(cin, relation);
//            cout << "Status (open/closed): ";
//            getline(cin, status);
//            graph.addPath(building1, building2, weight, relation, status);
//            break;
//        case 4:
//            cout << "\n--- Remove Path ---\nSource Building: ";
//            getline(cin, building1);
//            cout << "Destination Building: ";
//            getline(cin, building2);
//            graph.removePath(building1, building2);
//            break;
//        case 5:
//            cout << "\n--- Shortest Path ---\nSource Building: ";
//            getline(cin, building1);
//            cout << "Destination Building: ";
//            getline(cin, building2);
//            graph.shortestPath(building1, building2);
//            break;
//        case 6:
//            cout << "\n--- BFS Traversal ---\nStart Building: ";
//            getline(cin, building1);
//            graph.BFS(building1);
//            break;
//        case 7:
//            cout << "\n--- DFS Traversal ---\nStart Building: ";
//            getline(cin, building1);
//            graph.DFS(building1);
//            break;
//        case 8:
//            graph.displayAdjacencyList();
//            break;
//        case 9:
//            cout << "Returning to main menu...\n";
//            break;
//        default:
//            cout << "Invalid choice!\n";
//        }
//    } while (choice != 9);
//}
//
//void roomsMenu(CampusGraph& graph, HashTable& hashTable, MessagingSystem& messaging) {
//    int choice;
//    string currentBuilding = "";
//    AVLTree* currentTree = NULL;
//    do {
//        cout << "\n========== ROOMS & SCHEDULING MENU ==========\n";
//        if (currentBuilding != "")
//            cout << "[Currently selected: " << currentBuilding << "]\n";
//        cout << "1. Select Building\n2. Insert Room\n3. Delete Room\n4. Search Room\n5. Search Rooms by Type\n6. Reserve Room\n7. Cancel Reservation\n8. Print Inorder\n9. Print Preorder\n10. Print Postorder\n11. Back\n";
//        cout << "=============================================\nEnter choice: ";
//        cin >> choice;
//        cin.ignore();
//        string roomID, buildingName, roomType, userName;
//        int floor;
//        switch (choice) {
//        case 1:
//            cout << "\n--- Select Building ---\nBuilding Name: ";
//            getline(cin, buildingName);
//            currentTree = graph.getBuildingRoomTree(buildingName);
//            if (currentTree) {
//                currentBuilding = buildingName;
//                cout << "Building '" << buildingName << "' selected!" << endl;
//            }
//            else {
//                cout << "Error: Building not found!" << endl;
//                currentBuilding = "";
//            }
//            break;
//        case 2:
//            if (!currentTree) {
//                cout << "Error: Please select a building first!" << endl;
//                break;
//            }
//            cout << "\n--- Insert Room ---\nRoom ID: ";
//            getline(cin, roomID);
//            cout << "Floor Number: ";
//            cin >> floor;
//            cin.ignore();
//            cout << "Room Type (classroom/lab/office): ";
//            getline(cin, roomType);
//            currentTree->insertRoom(roomID, floor, roomType);
//            break;
//        case 3:
//            if (!currentTree) {
//                cout << "Error: Please select a building first!" << endl;
//                break;
//            }
//            cout << "\n--- Delete Room ---\nRoom ID: ";
//            getline(cin, roomID);
//            currentTree->deleteRoom(roomID);
//            break;
//        case 4:
//            if (!currentTree) {
//                cout << "Error: Please select a building first!" << endl;
//                break;
//            }
//            cout << "\n--- Search Room ---\nRoom ID: ";
//            getline(cin, roomID);
//            currentTree->searchRoom(roomID);
//            break;
//        case 5:
//            if (!currentTree) {
//                cout << "Error: Please select a building first!" << endl;
//                break;
//            }
//            cout << "\n--- Search Rooms by Type ---\nRoom Type: ";
//            getline(cin, roomType);
//            currentTree->searchRoomsByType(roomType);
//            break;
//        case 6:
//            if (!currentTree) {
//                cout << "Error: Please select a building first!" << endl;
//                break;
//            }
//            cout << "\n--- Reserve Room ---\nRoom ID: ";
//            getline(cin, roomID);
//            cout << "Username: ";
//            getline(cin, userName);
//            // MODULE F: Validate user existence
//            if (!hashTable.searchUser(userName)) {
//                cout << "Error: User not found! Please register first." << endl;
//                cout << "Cross-validation failed!" << endl;
//                break;
//            }
//            // MODULE F: Reserve with notification system
//            if (currentTree->reserveRoom(roomID, userName, &messaging)) {
//                // MODULE F: Update user's last booked room
//                hashTable.updateLastBookedRoom(userName, currentBuilding + "-" + roomID);
//                cout << "Room tracking updated in user profile!" << endl;
//            }
//            break;
//        case 7:
//            if (!currentTree) {
//                cout << "Error: Please select a building first!" << endl;
//                break;
//            }
//            cout << "\n--- Cancel Reservation ---\nRoom ID: ";
//            getline(cin, roomID);
//            currentTree->cancelReservation(roomID);
//            break;
//        case 8:
//            if (!currentTree) {
//                cout << "Error: Please select a building first!" << endl;
//                break;
//            }
//            currentTree->printInorder();
//            break;
//        case 9:
//            if (!currentTree) {
//                cout << "Error: Please select a building first!" << endl;
//                break;
//            }
//            currentTree->printPreorder();
//            break;
//        case 10:
//            if (!currentTree) {
//                cout << "Error: Please select a building first!" << endl;
//                break;
//            }
//            currentTree->printPostorder();
//            break;
//        case 11:
//            cout << "Returning to main menu...\n";
//            break;
//        default:
//            cout << "Invalid choice!\n";
//        }
//    } while (choice != 11);
//}
//
//void complaintsMenu(ComplaintQueue& complaints, HashTable& hashTable) {
//    int choice;
//    do {
//        cout << "\n========== COMPLAINTS MENU ==========\n";
//        cout << "1. Submit New Complaint\n2. Process Next Complaint\n3. View Next Complaint\n4. Display All Pending\n5. Complaint Statistics\n6. Back\n";
//        cout << "=====================================\nEnter choice: ";
//        cin >> choice;
//        cin.ignore();
//        string raisedBy, building, roomID, description, timestamp;
//        switch (choice) {
//        case 1:
//            cout << "\n--- Submit Complaint ---\nYour Username: ";
//            getline(cin, raisedBy);
//            // MODULE F: Validate user existence
//            if (!hashTable.searchUser(raisedBy)) {
//                cout << "Error: User not found! Please register first." << endl;
//                cout << "User validation failed!" << endl;
//                break;
//            }
//            cout << "Building: ";
//            getline(cin, building);
//            cout << "Room ID: ";
//            getline(cin, roomID);
//            cout << "Description: ";
//            getline(cin, description);
//            cout << "Timestamp (e.g., 2024-01-15 10:30): ";
//            getline(cin, timestamp);
//            complaints.enqueue(raisedBy, building, roomID, description, timestamp);
//            cout << "Complaint submitted with validated user!" << endl;
//            break;
//        case 2:
//            complaints.processNextComplaint();
//            break;
//        case 3:
//            complaints.peek();
//            break;
//        case 4:
//            complaints.displayQueue();
//            break;
//        case 5:
//            complaints.displayStatistics();
//            break;
//        case 6:
//            cout << "Returning to main menu...\n";
//            break;
//        default:
//            cout << "Invalid choice!\n";
//        }
//    } while (choice != 6);
//}
//
//void messagingMenu(MessagingSystem& messaging, HashTable& hashTable) {
//    int choice;
//    do {
//        cout << "\n========== MESSAGING MENU ==========\n";
//        cout << "1. Send Message\n2. View Latest Message\n3. Pop Latest Message\n4. Display Conversation\n5. Back\n";
//        cout << "====================================\nEnter choice: ";
//        cin >> choice;
//        cin.ignore();
//        string fromUser, toUser, messageText, timestamp;
//        switch (choice) {
//        case 1:
//            cout << "\n--- Send Message ---\nFrom (your username): ";
//            getline(cin, fromUser);
//            // MODULE F: Validate sender
//            if (!hashTable.searchUser(fromUser)) {
//                cout << "Error: Sender not found! Please register first." << endl;
//                cout << "Sender validation failed!" << endl;
//                break;
//            }
//            cout << "To (recipient username): ";
//            getline(cin, toUser);
//            // MODULE F: Validate recipient
//            if (!hashTable.searchUser(toUser)) {
//                cout << "Error: Recipient not found!" << endl;
//                cout << "Recipient validation failed!" << endl;
//                break;
//            }
//            cout << "Message: ";
//            getline(cin, messageText);
//            cout << "Timestamp (e.g., 2024-01-15 10:30): ";
//            getline(cin, timestamp);
//            messaging.sendMessage(fromUser, toUser, messageText, timestamp);
//            cout << "Message sent with validated users!" << endl;
//            break;
//        case 2:
//            cout << "\n--- View Latest Message ---\nYour Username: ";
//            getline(cin, fromUser);
//            cout << "Friend's Username: ";
//            getline(cin, toUser);
//            messaging.viewLatestMessage(fromUser, toUser);
//            break;
//        case 3:
//            cout << "\n--- Pop Latest Message ---\nYour Username: ";
//            getline(cin, fromUser);
//            cout << "Friend's Username: ";
//            getline(cin, toUser);
//            messaging.popLatestMessage(fromUser, toUser);
//            break;
//        case 4:
//            cout << "\n--- Display Conversation ---\nUser 1: ";
//            getline(cin, fromUser);
//            cout << "User 2: ";
//            getline(cin, toUser);
//            messaging.displayConversation(fromUser, toUser);
//            break;
//        case 5:
//            cout << "Returning to main menu...\n";
//            break;
//        default:
//            cout << "Invalid choice!\n";
//        }
//    } while (choice != 5);
//}
//
//void moduleFDemoMenu(HashTable& hashTable, CampusGraph& graph, ComplaintQueue& complaints, MessagingSystem& messaging) {
//    int choice;
//    do {
//        cout << "\n========== INTEGRATION & SMART FEATURES ==========\n";
//        cout << "1. Demo: Room Reservation with Tracking\n";
//        cout << "2. Demo: Double-Booking Prevention\n";
//        cout << "3. Demo: User Deletion with Reservation Cleanup\n";
//        cout << "4. Demo: Building Removal with Data Cleanup\n";
//        cout << "5. Demo: Cross-Module Validation\n";
//        cout << "6. View Integration Status\n";
//        cout << "7. Back to Main Menu\n";
//        cout << "============================================================\n";
//        cout << "Enter choice: ";
//        cin >> choice;
//        cin.ignore();
//
//        string userName, buildingName, roomID, userName2;
//
//        switch (choice) {
//        case 1:
//            cout << "\n========== DEMO: Room Reservation with Tracking ==========\n";
//            cout << "This demo shows:\n";
//            cout << "- Automatic lastBookedRoom update in user profile\n";
//            cout << "- Notification sent to user upon reservation\n\n";
//
//            cout << "Enter username: ";
//            getline(cin, userName);
//            if (!hashTable.searchUser(userName)) {
//                cout << "Error: User not found! Create user first.\n";
//                break;
//            }
//
//            cout << "Enter building name: ";
//            getline(cin, buildingName);
//            cout << "Enter room ID: ";
//            getline(cin, roomID);
//
//            {
//                AVLTree* tree = graph.getBuildingRoomTree(buildingName);
//                if (!tree) {
//                    cout << "Error: Building not found!\n";
//                    break;
//                }
//
//                cout << "\nStarting integrated reservation...\n";
//                if (tree->reserveRoom(roomID, userName, &messaging)) {
//                    hashTable.updateLastBookedRoom(userName, buildingName + "-" + roomID);
//                    cout << "\nIntegration Complete!\n";
//                    cout << "- Room reserved\n";
//                    cout << "- User profile updated\n";
//                    cout << "- Notification sent\n";
//                    hashTable.displayUserDetails(userName);
//                }
//            }
//            break;
//
//        case 2:
//            cout << "\n========== DEMO: Double-Booking Prevention ==========\n";
//            cout << "This demo shows prevention of double-booking\n\n";
//
//            cout << "Enter building name: ";
//            getline(cin, buildingName);
//            cout << "Enter room ID (already reserved): ";
//            getline(cin, roomID);
//            cout << "Enter username trying to book: ";
//            getline(cin, userName);
//
//            {
//                AVLTree* tree = graph.getBuildingRoomTree(buildingName);
//                if (!tree) {
//                    cout << "Error: Building not found!\n";
//                    break;
//                }
//
//                cout << "\nAttempting reservation...\n";
//                tree->reserveRoom(roomID, userName, &messaging);
//                cout << "\nSystem prevented conflict!\n";
//            }
//            break;
//
//        case 3:
//            cout << "\n========== DEMO: User Deletion with Cleanup ==========\n";
//            cout << "This demo shows:\n";
//            cout << "- Cancellation of all user's room reservations\n";
//            cout << "- Cross-module data consistency\n\n";
//
//            cout << "Enter username to delete: ";
//            getline(cin, userName);
//
//            cout << "\nStarting integrated deletion...\n";
//            if (hashTable.deleteUser(userName, &graph)) {
//                cout << "\nIntegration Complete!\n";
//                cout << "- User account deleted\n";
//                cout << "- All reservations cancelled\n";
//                cout << "- Data consistency maintained\n";
//            }
//            break;
//
//        case 4:
//            cout << "\n========== DEMO: Building Removal with Cleanup ==========\n";
//            cout << "This demo shows:\n";
//            cout << "- Removal of all rooms in building\n";
//            cout << "- Clearing related complaints\n";
//            cout << "- Graph edge cleanup\n\n";
//
//            cout << "Enter building name to remove: ";
//            getline(cin, buildingName);
//
//            cout << "\nStarting integrated building removal...\n";
//            if (graph.removeBuilding(buildingName, &complaints)) {
//                cout << "\nIntegration Complete!\n";
//                cout << "- Building removed from graph\n";
//                cout << "- All rooms deleted\n";
//                cout << "- Related complaints cleared\n";
//                cout << "- All edges removed\n";
//            }
//            break;
//
//        case 5:
//            cout << "\n========== DEMO: Cross-Module Validation ==========\n";
//            cout << "This demo shows validation across modules\n\n";
//
//            cout << "Test 1: Submit complaint with invalid user\n";
//            complaints.enqueue("NonExistentUser", "TestBuilding", "101", "Test", "2024-01-01");
//
//            cout << "\nTest 2: Send message between users\n";
//            cout << "From username: ";
//            getline(cin, userName);
//            cout << "To username: ";
//            getline(cin, userName2);
//
//            if (hashTable.searchUser(userName) && hashTable.searchUser(userName2)) {
//                messaging.sendMessage(userName, userName2, "Test message", "2024-01-01");
//                cout << "Both users validated successfully!\n";
//            }
//            else {
//                cout << "Validation failed - user(s) not found!\n";
//            }
//            break;
//
//        case 6:
//            cout << "\n========== INTEGRATION STATUS ==========\n";
//            cout << "Integeration Features Implemented:\n\n";
//            cout << "1. Room Reservation Tracking:\n";
//            cout << "  - lastBookedRoom updated automatically\n";
//            cout << "  - Notifications sent on reservation\n";
//            cout << "  - Double-booking prevention active\n\n";
//
//            cout << "2. Cross-Module Data Consistency:\n";
//            cout << "  - User deletion cancels all reservations\n";
//            cout << "  - Building removal clears all rooms\n";
//            cout << "  - User validation before complaints\n";
//            cout << "  - User validation before messaging\n\n";
//
//            cout << "3. Smart Features:\n";
//            cout << "  - Automatic notification system\n";
//            cout << "  - Integrated error handling\n";
//            cout << "  - Data synchronization across modules\n";
//            cout << "========================================\n";
//            break;
//
//        case 7:
//            cout << "Returning to main menu...\n";
//            break;
//
//        default:
//            cout << "Invalid choice!\n";
//        }
//    } while (choice != 7);
//}
//
//// ==================== MAIN FUNCTION ====================
//int main() {
//    HashTable userDirectory;
//    CampusGraph campusMap;
//    ComplaintQueue complaintSystem;
//    MessagingSystem messagingSystem;
//    int choice;
//
//    cout << "============================================\n";
//    cout << "        UNIVERSITY MANAGEMENT SYSTEM       \n";
//    cout << "   Complete Implementation - All Modules   \n";
//    cout << "============================================\n";
//
//    do {
//        cout << "\n================ MAIN MENU =================\n";
//        cout << "1. User & Authentication (Hash Table)\n";
//        cout << "2. Campus Map (Graph)\n";
//        cout << "3. Rooms & Scheduling (AVL Tree)\n";
//        cout << "4. Complaints (Queue)\n";
//        cout << "5. Messaging (Stacks)\n";
//        cout << "6. Integration Features\n";
//        cout << "7. Exit\n";
//        cout << "============================================\n";
//        cout << "Enter choice: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1:
//            userDirectoryMenu(userDirectory, campusMap);
//            break;
//        case 2:
//            campusMapMenu(campusMap, complaintSystem);
//            break;
//        case 3:
//            roomsMenu(campusMap, userDirectory, messagingSystem);
//            break;
//        case 4:
//            complaintsMenu(complaintSystem, userDirectory);
//            break;
//        case 5:
//            messagingMenu(messagingSystem, userDirectory);
//            break;
//        case 6:
//            moduleFDemoMenu(userDirectory, campusMap, complaintSystem, messagingSystem);
//            break;
//        case 7:
//            cout << "\n============================================\n";
//            cout << "   Thank you for using the system!         \n";
//            cout << "   Goodbye!                                \n";
//            cout << "============================================\n";
//            break;
//        default:
//            cout << "Invalid choice! Please try again.\n";
//        }
//    } while (choice != 7);
//
//    return 0;
//}
//
