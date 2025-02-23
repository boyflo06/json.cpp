/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:52:13 by fghysbre          #+#    #+#             */
/*   Updated: 2025/02/23 14:49:30 by fghysbre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JSON.hpp"
#include <iostream>

int main(void) {
	JSON json;
    
    json["name"] = "Jhon Doe";
    json["age"] = 30;
    json["is_student"] = false;
    json["gpa"] = 3.5;

    json["address"]["street"] = "123 Main St";
    json["address"]["city"] = "Anytown";

    json["phone_numbers"] = JSONArray();
    {
        JSON    &pn = json["phone_numbers"];
        if (!pn.value.holds_alternative(ARRAY))
            pn = JSONArray();
        JSONArray   &arr = pn.value.getArr();
        arr.push_back("123-456-7890");
        arr.push_back("987-654-3210");
    }
    std::cout << json.serialize() << std::endl;
    
    JSON parsed = JSON::parse("{\"address\": {}}");

    std::cout << parsed.serialize() << std::endl;
}