// Author: Nishant Sharma
// Created: 2026-05-06 10:54:45
#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

class DocumentElement{
    virtual String render() = 0;
};

class TextElement : public DocumentElement{
    private:
        string text;

    public:
        TextElement(string text){
            this->text = text;
        }

        string render() override{
            return text;
        }
};

class ImageElement : public DocumentElement{
    private:     
        string image;

    public:
        ImageElement(string image){
            this->image = image;
        }

        string render() override{
            return "[Image: ]" + image + "]";
        }
};

class Document{
    private:
        vector<DocumentElement*> documentElements;

    public:
        void addElement(DocumentElement* element) {
            documentElements.push_back(element);
        }

        string render() {
        string result;
        for (auto element : documentElements) {
            result += element->render();
        }
        return result;
    }
};

class persistance{
    virtual void save() = 0;
};

class saveToDb : public persistance{
    public:
        void save() override{
            // save to db
        }
};

class saveToFile : public persistance{
    public:
        void save() override{
            // save to file
        }
};



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

}