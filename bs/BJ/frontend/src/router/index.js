import Vue from 'vue'
import Router from 'vue-router'

Vue.use(Router)

/* Layout */
import Layout from '@/layout'
import store from "@/store";

/**
 * Note: sub-menu only appear when route children.length >= 1
 * Detail see: https://panjiachen.github.io/vue-element-admin-site/guide/essentials/router-and-nav.html
 *
 * hidden: true                   if set true, item will not show in the sidebar(default is false)
 * alwaysShow: true               if set true, will always show the root menu
 *                                if not set alwaysShow, when item has more than one children route,
 *                                it will becomes nested mode, otherwise not show the root menu
 * redirect: noRedirect           if set noRedirect will no redirect in the breadcrumb
 * name:'router-name'             the name is used by <keep-alive> (must set!!!)
 * meta : {
    roles: ['admin','editor']    control the page roles (you can set multiple roles)
    title: 'title'               the name show in sidebar and breadcrumb (recommend set)
    icon: 'svg-name'/'el-icon-x' the icon show in the sidebar
    breadcrumb: false            if set false, the item will hidden in breadcrumb(default is true)
    activeMenu: '/example/list'  if set path, the sidebar will highlight the path you set
  }
 */

/**
 * constantRoutes
 * a base page that does not have permission requirements
 * all roles can be accessed
 */
export const constantRoutes = [
  {
    path: '/login',
    component: () => import('@/views/login/index'),
    hidden: true
  },

  {
    path: '/',
    redirect: '/login',
  },

  {
    path: '/dashboard',
    component: Layout,
    children: [
      {
        path: 'index',
        name: '首页',
        component: () => import('@/views/dashboard/index'),
        meta: { title: '首页', icon: 'home'}
      }
    ]
  },

  {
    path: '/like',
    component: Layout,
    children: [
      {
        path: 'index',
        name: '我喜欢的',
        component: () => import('@/views/like/index'),
        meta: { title: '我喜欢的', icon: 'like'}
      }
    ]
   },

  {
    path: '/price',
    component: Layout,
    children: [
      {
        path: 'index',
        name: '历史价格',
        component: () => import('@/views/price/index'),
        meta: { title: '历史价格', icon: 'price'}
      }
    ]
   },

  {
    path: '/info',
    component: Layout,
    children: [
      {
        path: 'index',
        name: '个人中心',
        component: () => import('@/views/info/index'),
        meta: { title: '个人中心', icon: 'info'}
      }
    ]
   },



  // 输入错误 URL 重定向到登录页面或首页
  { path: '*', redirect: '/', hidden: true }
]

const createRouter = () => new Router({
  // mode: 'history', // require service support
  scrollBehavior: () => ({ y: 0 }),
  routes: constantRoutes
})

const router = createRouter()


// Detail see: https://github.com/vuejs/vue-router/issues/1234#issuecomment-357941465
export function resetRouter() {
  const newRouter = createRouter()
  router.matcher = newRouter.matcher // reset router
}

export default router
