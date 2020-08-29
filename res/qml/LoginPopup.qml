import QtQuick 2.4
import org.pruefungsplaner.ConnectionManager 1.0

LoginPopupForm {
    id: loginPopup
    property alias backgroundSource: loginPopup.backgroundSource

    Connections{
        target: ConnectionManager
        function onLoginError(message) {
            errorLabel.text = message;
            passwordField.text = "";
            passwordField.focus = true;
        }

        function onLoginSuccess(){
            loginPopup.close();
        }
    }

    Connections{
        target: passwordField
        function onAccepted() {
            ConnectionManager.login(usernameField.text, passwordField.text);
        }
    }

    Connections{
        target: usernameField
        function onAccepted() {
            passwordField.focus = true;
        }
    }

    Connections{
        target: loginButton
        function onClicked() {
            ConnectionManager.login(usernameField.text, passwordField.text);
        }
    }

    onOpened: {
        usernameField.focus = true;
    }
}
