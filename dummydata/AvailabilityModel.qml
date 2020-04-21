import QtQuick 2.0

ListModel {
    ListElement {
        week: "Woche 1"

        hourNames: [
            ListElement { name: "1" },
            ListElement { name: "2" },
            ListElement { name: "3" },
            ListElement { name: "4" },
            ListElement { name: "5" },
            ListElement { name: "6" }
        ]

        days: [
            ListElement {
                day: "Montag 4.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Dienstag 5.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Mittwoch 6.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: true },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Donnerstag 7.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: true },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Freitag 8.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: true },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Samstag 9.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: true }
                ]
            }
        ]
    }

    ListElement {
        week: "Woche 2"

        hourNames: [
            ListElement { name: "1" },
            ListElement { name: "2" },
            ListElement { name: "3" },
            ListElement { name: "4" },
            ListElement { name: "5" },
            ListElement { name: "6" }
        ]

        days: [
            ListElement {
                day: "Montag 11.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Dienstag 12.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Mittwoch 13.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: true },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Donnerstag 14.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: true },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Freitag 15.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: true },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Samstag 16.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: true }
                ]
            }
        ]
    }

    ListElement {
        week: "Woche 3"

        hourNames: [
            ListElement { name: "1" },
            ListElement { name: "2" },
            ListElement { name: "3" },
            ListElement { name: "4" },
            ListElement { name: "5" },
            ListElement { name: "6" }
        ]

        days: [
            ListElement {
                day: "Montag 18.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Dienstag 19.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Mittwoch 20.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: true },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Donnerstag 21.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: true },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Freitag 22.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: false },
                    ListElement { available: true },
                    ListElement { available: true }
                ]
            },
            ListElement {
                day: "Samstag 23.1"
                hours: [
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: true },
                    ListElement { available: true }
                ]
            }
        ]
    }
}
