/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fghysbre <fghysbre@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:52:13 by fghysbre          #+#    #+#             */
/*   Updated: 2025/02/22 23:20:55 by fghysbre         ###   ########.fr       */
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
        if (!json["phone_numbers"].value.holds_alternative(ARRAY))
            json["phone_numbers"] = JSONArray();
        JSONArray   &arr = json["phone_numbers"].value.getArr();
        arr.push_back("123-456-7890");
        arr.push_back("987-654-3210");
    }

    std::cout << json.serialize() << std::endl;
    return 0;
}