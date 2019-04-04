mediaLibraryServerModule.controller('mediaLibraryServer', function($scope, $window) {
    $scope.login = $window.localStorage.getItem('login');
});