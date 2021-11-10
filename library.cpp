#include <stdio.h>
#include <vector>
#include "library.h"


/* Document definitions */
void Document::updateTitle(const char *newTitle) {
	*_title = newTitle;
}
void Document::updateYear(int newYear) {
	_year = newYear;
}
void Document::updateQuantity(int newQuantity) {
	_quantity = newQuantity;
}
char *Document::getTitle() {
	return *_title;
}
int Document::getYear() {
	return _year;
}
int Document::borrowDoc() {
	if (_quantity > 0) {
		_quantity = _quantity - 1;
		return 0;
	}
	return 1;
}
void Document::returnDoc() {
	_quantity = _quantity + 1;
}

/* Novel Definitions */

Novel::Novel(const char *title, const char *author, int year, int quantity) {
	*_title = title;
	*_author = author;
	_year = year;
	_quantity = quantity;
}

document_type Novel::getDocType() {
	return DOC_NOVEL;
}

void Novel::print() {
	printf("novel, title: %s, author: %s, year: %d, quantity: %d", _title, _author, _year, _quantity);
}

void Novel::updateAuthor(const char *newAuthor) {
	*_author = newAuthor;
}
char *Novel::getAuthor() {
	return &_author;
}


/* Comic Definitions */

Comic::Comic(const char *title, const char *author, int issue, int year, int quantity) {
	*_title = title;
	*_author = author;
	_issue = issue;
	_year = year;
	_quantity = quantity;
}

document_type Comic::getDocType() {
	return DOC_COMIC;
}

printf("Comic, title: %s, author: %s, issue: %d, year: %d, quantity: %d", _title, _author, _issue, _year, _quantity);

void Comic::updateAuthor(const char *newAuthor) {
	*_author = newAuthor;
}

void Comic::updateIssue(int newIssue) {
	_issue = newIssue;
}

char *Comic::getAuthor() {
	return &_author;
}

int Comic::getIssue() {
	return _issue;
}

/* Magazine Definitions*/

Magazine::Magazine(const char *title, int issue, int year, int quantity) {
	*_title = title;
	_issue = issue;
	_year = year;
	_quantity = quantity;
}

document_type Magazine::getDocType() {
	return DOC_MAGAZINE;
}

void Magazine::print() {
	printf("Magazine, title: %s, issue: %d, year: %d, quantity: %d", _title, _issue, _year, _quantity);
}

void Magainze::updateIssue(int newIssue) {
	_issue = newIssue;
}

int Magazine::getIssue() {
	return _issue;
}

Library::Library() {

}

void Library::print() {
	for (int i = 0; i < _docs.size(); i++) {
		_docs[i].print();
	}
}

Document *Library::searchDocument(const char *title) {
	for (int i = 0; i <_docs.size(); i++) {
		if (title == _docs[i]) {
			return &_docs[i];
		}
	}
	return NULL;
}

int Library::addDocument(Document *d) {
	for (int i = 0; i < _docs.size(); i++) {
		if (d.getTitle() == _docs[i].getTitle()){
			return 1;
		}
	}

	_docs.push_back(d);
	return 0;
}

int Library::delDocument(const char *title) {
	for (int i = 0; i < _docs.size(); i++) {
		if (title == _docs[i].getTitle()){
			_docs.erase(i);
			return 0;
		}
	}
	return 1;
}

int Library::borrowDoc(const char *title) {
	Document doc = searchDocument(title)
	if (searchDocument(title) != NULL) {
		if (doc.borrowDoc() == 0) {
			return 0;
		}
	}
	return 1;
}
int Library::returnDoc(const char *title) {
	Document doc = searchDocument(title)
	if (searchDocument(title) != NULL) {
		doc.returnDoc();
		return 0;
	}
	return 1;
}