import QtQuick 2.4
import org.pruefungsplaner.ConnectionManager 1.0

LoginPopupForm {
    id: loginPopup
    property alias backgroundSource: loginPopup.backgroundSource

    Connections{
        target: ConnectionManager
        function onLoginError(message) {
            errorLabel.text = message;
        }

        function onLoginSuccess(){
            loginPopup.close();
        }
    }

    Connections{
        target: loginButton
        onClicked: {
            ConnectionManager.login(usernameField.text, passwordField.text);
        }
    }
}
