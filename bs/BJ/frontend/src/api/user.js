import request from '@/utils/request'

export function login(user) {
  return request({
    url: '/compare/login/',
    method: 'post',
    data: {
      method: 'login',
      username: user.username,
      password: user.password
    }
  })
}

export function register(user) {
  return request({
    url: '/compare/login/',
    method: 'post',
    data: {
      method: 'register',
      username: user.username,
      password: user.password,
      email: user.email
    }
  })
}

export function getInfo(token) {
  return request({
    url: 'compare/login/',
    method: 'get',
    params: { token }
  })
}

export function logout(token) {
  return request({
    url: 'compare/login/',
    method: 'post',
    data: {
      method: 'logout',
      token
    }
  })
}
