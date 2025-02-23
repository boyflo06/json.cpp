/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSON::parse.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:40:13 by fghysbre          #+#    #+#             */
/*   Updated: 2025/02/23 15:21:47 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JSON.hpp"
#include <iostream>

JSON	parser(const std::string&str, std::string::const_iterator &it) {
    JSON	ret;
	if (*it == '{') {
		ret = JSONObject();
		it += 1;
		while (true) {
			if (*it == '}') {
				it++;
				return ret;
			}
			it += 1;
			size_t start = it - str.begin();
			size_t delimpos = str.find("\": ", start);
			std::string key = str.substr(start, delimpos - start);
			ret[key] = parser(str, (it = str.begin() + delimpos + 3));
			if ((it - str.begin()) + 5 <= str.size() && !str.compare(it - str.begin(), 2, ", "))
				it += 2;
		}
	} else if (*it == '[') {
		ret = JSONArray();
		JSONArray arr;
		it++;
		while (true) {
			if (*it == ']') {
				it++;
				ret = arr;
				return ret;
			}
			arr.push_back(parser(str, it));
			if ((it - str.begin()) + 2 <= str.size() && !str.compare(it - str.begin(), 2, ", "))
				it += 2;
		}
	} else if (*it == '"') {
		it++;
		ret = str.substr(it - str.begin(), str.find('"', it - str.begin()) - (it - str.begin()));
		it = str.begin() +  str.find('"', it - str.begin()) + 1;
		return ret;
	} else if ((it - str.begin()) + 4 <= str.size() && !str.compare(it - str.begin(), 4, "true")) {
		ret = true;
		it += 4;
		return ret;
	} else if ((it - str.begin()) + 5 <= str.size() && !str.compare(it - str.begin(), 5, "false")) {
		ret = false;
		it += 5;
		return ret;
	} else if ((it - str.begin()) + 4 <= str.size() && !str.compare(it - str.begin(), 4, "null")) {
		ret = ft_nullptr;
		it += 4;
		return ret;
	} else {
		size_t	size = it - str.begin();
		while (size < str.length() && str[size] != ',' && str[size] != '}' && str[size] != ']') size++;
		size = size - (it - str.begin());
		std::string	num = str.substr(it - str.begin(), size);
		std::stringstream ss(num);
		if (num.find('.') != std::string::npos) {
			double	res;
			ss >> res;
			ret = res;
		} else {
			int		res;
			ss >> res;
			ret = res;
		}
		it = it + size;
		return ret;
	}
	return ret;
}

JSON JSON::parse(const std::string& str) {
	std::string::const_iterator	it = str.begin();
	return parser(str, it);
}