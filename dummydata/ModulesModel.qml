import QtQuick 2.0


ListModel {
    ListElement {
        name: "PAD1"
        number: "30.1234"
        origin: "FBI"
        groups: [
            ListElement { group: "bachelor 1 a"},
            ListElement { group: "bachelor 1 b"},
            ListElement { group: "bachelor 1 a"},
            ListElement { group: "bachelor 1 b"},
            ListElement { group: "bachelor 1 a"},
            ListElement { group: "bachelor 1 b"},
            ListElement { group: "bachelor 1 a"},
            ListElement { group: "bachelor 1 b"},
            ListElement { group: "bachelor 1 a"},
            ListElement { group: "bachelor 1 b"},
            ListElement { group: "bachelor 1 c"}
        ]
        constraints: [
            ListElement { constraint: "woche 1" }
        ]
        active: true
    }

    ListElement {
        name: "PAD2"
        number: "30.5353"
        origin: "FBI"
        groups: [
            ListElement { group: "bachelor 2 a"},
            ListElement {  group: "bachelor 2 b"}
        ]
        constraints: [
            ListElement { constraint: "woche 2"}
        ]
        active: true
    }

    ListElement {
        name: "Grundlagen der Analysis"
        number: "30.5345"
        origin: "MN"
        groups: [
            ListElement { group: "bachelor 4 a"},
            ListElement { group: "bachelor 4 b"}
        ]
        constraints: [
        ]
        active: false
    }

}
