
﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AnimalShelter
{
    public class Cat : Animal
    {
        /// <summary>
        /// Description of the bad habits that the cat has (e.g. "Scratches the couch").
        /// or null if the cat has no bad habits.
        /// </summary>
        public string BadHabits { get; set; }

        /// <summary>
        /// Calculates and returns the price of the cat.
        /// </summary>
        public override decimal Price
        {
            get
            {
                if (BadHabits.Length < 40)
                {
                    return 60m - BadHabits.Length;
                }
                else
                {
                    return 20m;
                }
            }
        }

        /// <summary>
        /// Creates a cat.
        /// </summary>
        /// <param name="chipRegistrationNumber">The chipnumber of the animal. 
        ///                                      Must be unique. Must be zero or greater than zero.</param>
        /// <param name="dateOfBirth">The date of birth of the animal.</param>
        /// <param name="name">The name of the animal.</param>
        /// <param name="badHabits">The bad habbits of the cat (e.g. "scratches the couch")
        ///                         or null if none.</param>
        public Cat(int chipRegistrationNumber, SimpleDate dateOfBirth,
                   string name, string badHabits) : base(chipRegistrationNumber, dateOfBirth, name)
        {
            if(String.IsNullOrWhiteSpace(badHabits))
            {
                this.BadHabits = null;
            }
            else if (chipRegistrationNumber >= 0)
            {
                this.BadHabits = badHabits;
            }
            else
            {
                throw new ArgumentOutOfRangeException();
            }
        }

        /// <summary>
        /// Retrieve information about this cat
        /// </summary>
        /// <returns>A string containing the information of this animal.
        ///          The format of the returned string is
        ///          "Cat: <ChipRegistrationNumber>, <DateOfBirth>, <Name>, <IsReserved>, <BadHabits>"
        ///          Where: IsReserved will be "reserved" if reserved or "not reserved" otherwise.
        ///                 BadHabits will be "none" if the cat has no bad habits, or the bad habits string otherwise.
        /// </returns>
        public override string ToString()
        {
            string IsReservedString;
            if (IsReserved)
            {
                IsReservedString = "reserved";
            }
            else
            {
                IsReservedString = "not reserved";
            }

            string badHabits;
            if(BadHabits == null)
            {
                badHabits = "None";
            }
            else
            {
                badHabits = BadHabits;
            }

            string info = ChipRegistrationNumber
                         + ", " + DateOfBirth
                         + ", " + Name
                         + ", " + IsReservedString
                         + ", " + badHabits;
            return info;
        }
    }
}
