/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSON.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:35:41 by fghysbre          #+#    #+#             */
/*   Updated: 2025/02/23 13:09:39 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JSON.hpp"
#include "assert.h"
#include <stdexcept>

void _JSONVariant::copyFrom(const _JSONVariant& other) {
	this->type = other.type;
	switch (this->type) {
		case (BOOL):
			new(storage.buffer) bool(other.getBool());
			break;
		case (INT):
			new(storage.buffer) int(other.getInt());
			break;
		case (DOUBLE):
			new(storage.buffer) double(other.getDouble());
			break;
		case (STRING):
			new(storage.buffer) std::string(other.getStr());
			break;
		case (OBJECT):
			new(storage.buffer) JSONObject(other.getObj());
			break;
		case (ARRAY):
			new(storage.buffer) JSONArray(other.getArr());
			break;
		default:
			break;
	}
}

void _JSONVariant::destroy() {
	switch (this->type) {
		case (BOOL):
			//delete reinterpret_cast<bool*>(storage.buffer);
			break;
		case (INT):
			//delete reinterpret_cast<int*>(storage.buffer);
			break;
		case (DOUBLE):
			//delete reinterpret_cast<double*>(storage.buffer);
			break;
		case (STRING):
			reinterpret_cast<std::string*>(storage.buffer)->~basic_string();
			break;
		case (OBJECT):
			reinterpret_cast<JSONObject*>(storage.buffer)->~map();
			break;
		case (ARRAY):
			reinterpret_cast<JSONArray*>(storage.buffer)->~vector();
			break;
		default:
			break;
	}
}

_JSONVariant::_JSONVariant() : type(NONE) {}

_JSONVariant::_JSONVariant(ft_nullptr_t): type(NILL) {
	new(storage.buffer) ft_nullptr_t();
}

_JSONVariant::_JSONVariant(bool b): type(BOOL) {
	new(storage.buffer) bool(b);
}

_JSONVariant::_JSONVariant(int i): type(INT) {
	new(storage.buffer) int(i);
}

_JSONVariant::_JSONVariant(double d): type(DOUBLE) {
	new(storage.buffer) double(d);
}

_JSONVariant::_JSONVariant(const std::string& str): type(STRING) {
	new(storage.buffer) std::string(str);
}

_JSONVariant::_JSONVariant(const JSONObject& obj): type(OBJECT) {
	new(storage.buffer) JSONObject(obj);
}

_JSONVariant::_JSONVariant(const JSONArray& arr): type(ARRAY) {
	new(storage.buffer) JSONArray(arr);
}

_JSONVariant::_JSONVariant(const _JSONVariant& other) {
	this->copyFrom(other);
}

_JSONVariant::~_JSONVariant() {
	this->destroy();
}

_JSONVariant& _JSONVariant::operator=(const _JSONVariant& other) {
    if (this != &other) {
		this->destroy();
		this->copyFrom(other);
	}
	return *this;
}

bool _JSONVariant::isNill() const {
    return this->type == NILL;
}

bool _JSONVariant::isBool() const {
    return this->type == BOOL;
}

bool _JSONVariant::isInt() const {
    return this->type == INT;
}

bool _JSONVariant::isDouble() const {
    return this->type == DOUBLE;
}

bool _JSONVariant::isStr() const {
    return this->type == STRING;
}

bool _JSONVariant::isObj() const {
    return this->type == OBJECT;
}

bool _JSONVariant::isArr() const {
    return this->type == ARRAY;
}

const ft_nullptr_t _JSONVariant::getNill() const {
    assert(this->isNill());
	return ft_nullptr;
}

bool _JSONVariant::getBool() const {
    assert(this->isBool());
	return *reinterpret_cast<const bool*>(storage.buffer);
}

int _JSONVariant::getInt() const {
    assert(this->isInt());
	return *reinterpret_cast<const int*>(storage.buffer);
}

double _JSONVariant::getDouble() const {
    assert(this->isDouble());
	return *reinterpret_cast<const double*>(storage.buffer);
}

const std::string& _JSONVariant::getStr() const {
    assert(this->isStr());
	return *reinterpret_cast<const std::string*>(storage.buffer);
}

const JSONObject& _JSONVariant::getObj() const {
    assert(this->isObj());
	return *reinterpret_cast<const JSONObject*>(storage.buffer);
}

const JSONArray& _JSONVariant::getArr() const {
    assert(this->isArr());
	return *reinterpret_cast<const JSONArray*>(storage.buffer);
}

ft_nullptr_t _JSONVariant::getNill() {
    assert(this->isNill());
	return ft_nullptr;
}

bool _JSONVariant::getBool() {
    assert(this->isBool());
	return *reinterpret_cast<bool*>(storage.buffer);
}

int _JSONVariant::getInt() {
    assert(this->isInt());
	return *reinterpret_cast<int*>(storage.buffer);
}

double _JSONVariant::getDouble() {
    assert(this->isDouble());
	return *reinterpret_cast<double*>(storage.buffer);
}

std::string& _JSONVariant::getStr() {
    assert(this->isStr());
	return *reinterpret_cast<std::string*>(storage.buffer);
}

JSONObject& _JSONVariant::getObj() {
    assert(this->isObj());
	return *reinterpret_cast<JSONObject*>(storage.buffer);
}

JSONArray& _JSONVariant::getArr() {
    assert(this->isArr());
	return *reinterpret_cast<JSONArray*>(storage.buffer);
}

_JSONVariant& _JSONVariant::operator=(ft_nullptr_t) {
    this->destroy();
    this->type = NILL;
    new (storage.buffer) ft_nullptr_t();
    return (*this);
}

_JSONVariant& _JSONVariant::operator=(bool b) {
    this->destroy();
    this->type = BOOL;
    new (storage.buffer) bool(b);
    return (*this);
}

_JSONVariant& _JSONVariant::operator=(int i) {
	this->destroy();
	this->type = INT;
	new(storage.buffer) int(i);
	return (*this);
}
_JSONVariant& _JSONVariant::operator=(double d) {
	this->destroy();
	this->type = DOUBLE;
	new(storage.buffer) double(d);
	return (*this);
}
_JSONVariant& _JSONVariant::operator=(const std::string& str) {
	this->destroy();
	this->type = STRING;
	new(storage.buffer) std::string(str);
	return (*this);
}
_JSONVariant& _JSONVariant::operator=(const JSONObject& obj) {
	this->destroy();
	this->type = OBJECT;
	new(storage.buffer) JSONObject(obj);
	return (*this);
}
_JSONVariant& _JSONVariant::operator=(const JSONArray& arr) {
	this->destroy();
	this->type = ARRAY;
	new(storage.buffer) JSONArray(arr);
	return (*this);
}
bool _JSONVariant::holds_alternative(Type type) {
    return (this->type == type);
}


JSON::JSON(): value(ft_nullptr) {}

JSON::JSON(ft_nullptr_t): value(ft_nullptr) {}

JSON::JSON(bool b): value(b) {}

JSON::JSON(int i): value(i) {}

JSON::JSON(double d): value(d) {}

JSON::JSON(const char* s): value(std::string(s)) {}

JSON::JSON(const std::string& s): value(s) {}

JSON::JSON(const JSONArray& arr): value(arr) {}

JSON::JSON(const JSONObject& obj): value(obj) {}

JSON& JSON::operator=(const JSON& other) {
	value = other.value;
	return *this;
}

JSON& JSON::operator=(const std::string& s) {
	value = s;
	return *this;
}

JSON& JSON::operator=(const char* s) {
	value = std::string(s);
	return *this;
}

JSON& JSON::operator=(int i) {
	value = i;
	return *this;
}

JSON& JSON::operator=(bool b) {
	value = b;
	return *this;
}

JSON& JSON::operator=(double d) {
	value = d;
	return *this;
}

JSON& JSON::operator=(const JSONArray& arr) {
	value = arr;
	return *this;
}

JSON& JSON::operator=(const JSONObject& obj) {
	value = obj;
	return *this;
}

JSON& JSON::operator=(ft_nullptr_t) {
	value = ft_nullptr;
	return *this;
}

JSON& JSON::operator[](const std::string& key) {
	if (!this->value.holds_alternative(OBJECT))
		value = JSONObject();
	JSONObject	&obj = this->value.getObj();
	return obj[key];
}

const JSON& JSON::operator[](const std::string& key) const {
	const JSONObject& obj = this->value.getObj();
	return obj.at(key);
}

JSON& JSON::operator[](size_t index) {
	if (!this->value.holds_alternative(ARRAY))
		value = JSONArray();
	JSONArray arr = this->value.getArr();
	if (index >= arr.size())
		throw std::out_of_range("JSON array index out of range");
	return arr[index];
}

const JSON& JSON::operator[](size_t index) const {
	const JSONArray& arr = this->value.getArr();
	return arr.at(index);
}

std::string	JSON::serialize() const {
	std::stringstream ss;
	if (this->value.isNill())
		ss << "null";
	else if (this->value.isBool())
		ss << (this->value.getBool() ? "true" : "false");
	else if (this->value.isInt())
		ss << this->value.getInt();
	else if (this->value.isDouble())
		ss << this->value.getDouble();
	else if (this->value.isStr())
		ss << "\"" << this->value.getStr() << "\"";
	else if (this->value.isArr()) {
		ss << "[";
		const JSONArray				&arr = this->value.getArr();
		JSONArray::const_iterator	it = arr.begin();
		for (; it != arr.end(); ++it) {
			if (it != arr.begin())
				ss << ", ";
			ss << (*it).serialize();
		}
		ss << "]";
	} else if (this->value.isObj()) {
		ss << "{";
		const JSONObject			&arr = this->value.getObj();
		JSONObject::const_iterator	it = arr.begin();
		for (; it != arr.end(); ++it) {
			if (it != arr.begin())
				ss << ", ";
			ss << "\"" << (*it).first << "\": " << (*it).second.serialize();
		}
		ss << "}";
	}
	return (ss.str());
}


