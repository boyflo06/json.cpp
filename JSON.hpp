/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSON.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:16:52 by fghysbre          #+#    #+#             */
/*   Updated: 2025/02/22 23:33:34 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "nullptr.hpp"

class JSON;

typedef std::map<std::string, JSON> JSONObject;
typedef std::vector<JSON> JSONArray;

#define __MAX2(a, b) ((a) > (b) ? (a) : (b))
#define __MAX3(a, b, c) __MAX2(a, __MAX2(b, c))
#define __MAX4(a, b, c, d) __MAX2(a, __MAX3(b, c, d))
#define __MAX5(a, b, c, d, e) __MAX2(a, __MAX4(b, c, d, e))
#define __MAX6(a, b, c, d, e, f) __MAX2(a, __MAX5(b, c, d, e, f))
#define __MAX7(a, b, c, d, e, f, g) __MAX2(a, __MAX6(b, c, d, e, f, g))

enum Type { NILL, BOOL, INT, DOUBLE, STRING, ARRAY, OBJECT, NONE};

class _JSONVariant
{
	private:

	enum { StorageSize = (__MAX7(
		sizeof(ft_nullptr_t),
		sizeof(bool),
		sizeof(int),
		sizeof(double),
		sizeof(std::string),
		sizeof(JSONArray),
		sizeof(JSONObject)))
	};

	
	union Storage {
		char buffer[StorageSize];
		long double	align;	
	}		storage;
	Type	type;
	
	void	copyFrom(const _JSONVariant &other);
	void	destroy();
public:
	_JSONVariant();
	_JSONVariant(ft_nullptr_t);
	_JSONVariant(bool b);
	_JSONVariant(int i);
	_JSONVariant(double d);
	_JSONVariant(const std::string &str);
	_JSONVariant(const JSONObject &obj);
	_JSONVariant(const JSONArray &arr);
	_JSONVariant(const _JSONVariant &other);

	~_JSONVariant();

	_JSONVariant	&operator=(const _JSONVariant &other);

	bool	isNill() const;
	bool	isBool() const;
	bool	isInt() const;
	bool	isDouble() const;
	bool	isStr() const;
	bool	isObj() const;
	bool	isArr() const;

	const ft_nullptr_t		getNill() const;
	bool				getBool() const;
	int					getInt() const;
	double				getDouble() const;
	const std::string	&getStr() const;
	const JSONObject	&getObj() const;
	const JSONArray		&getArr() const;

	ft_nullptr_t	getNill();
	bool		getBool();
	int			getInt();
	double		getDouble();
	std::string	&getStr();
	JSONObject	&getObj();
	JSONArray	&getArr();

	_JSONVariant	&operator=(ft_nullptr_t);
	_JSONVariant	&operator=(bool b);
	_JSONVariant	&operator=(int i);
	_JSONVariant	&operator=(double d);
	_JSONVariant	&operator=(const std::string &str);
	_JSONVariant	&operator=(const JSONObject &obj);
	_JSONVariant	&operator=(const JSONArray &arr);
	

	bool	holds_alternative(Type type);
};

class JSON {
public:
	_JSONVariant	value;
	
	JSON();
	JSON(ft_nullptr_t);
	JSON(bool b);
	JSON(int i);
	JSON(double d);
	JSON(const char *s);
	JSON(const std::string& s);
	JSON(const JSONArray& arr);
	JSON(const JSONObject& obj);
	
	JSON	&operator=(const JSON &other);
	JSON	&operator=(const std::string &s);
	JSON	&operator=(const char *s);
	JSON	&operator=(int i);
	JSON	&operator=(bool b);
	JSON	&operator=(double d);
	
	JSON	&operator[](const std::string &key);
	const JSON	&operator[](const std::string &key) const;

	JSON	&operator[](size_t index);
	const JSON	&operator[](size_t index) const;

	std::string	serialize() const;
};

